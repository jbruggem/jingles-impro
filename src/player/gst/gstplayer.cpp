#include "gstplayer.h"

GstPlayer::GstPlayer(QObject *parent):
    IMediaPlayer(parent),
    playing(false),
    loaded(false),
    error(false),
    playingRequested(false),
    mustSeek(true),
    duration(-1),
    position(0),
    formatTime(GST_FORMAT_TIME),
    pipeline(0),
    gstObjectName("player")
{
    GstPlayer::ensureInitGst();
    connect(this,SIGNAL(requestPause()),this,SLOT(doPause()));
    connect(this,SIGNAL(requestPlay()),this,SLOT(doPlay()));
    connect(this,SIGNAL(requestStop()),this,SLOT(doStop()));
    //watcher = NULL;
    theVol = new GValue();
    g_value_init(theVol,G_TYPE_DOUBLE);

    positionQueryTimer = new QTimer(this);

}

void GstPlayer::buildPipeline(){
    QLOG_TRACE() << "GstPlayer::buildPipeline";

    pipeline = gst_element_factory_make("pipeline", gstObjectName.toUtf8().data());
    decodebin = gst_element_factory_make("uridecodebin",NULL);
    audioconvert = gst_element_factory_make("audioconvert",NULL);
    volume = gst_element_factory_make("volume",NULL);
    audiobin = gst_element_factory_make("autoaudiosink",NULL);


    gst_bin_add(GST_BIN(pipeline), decodebin);
    gst_bin_add(GST_BIN(pipeline), audioconvert);
    gst_bin_add(GST_BIN(pipeline), volume);
    gst_bin_add(GST_BIN(pipeline), audiobin);

    gst_element_link_many(volume, audioconvert, audiobin, NULL);

    // as soon as decodebin has a pad (i.e. file was loaded), connect it to volume
    g_signal_connect (decodebin, "pad-added", G_CALLBACK (GstPlayer::handleAddedPad), volume);

    // volume needs an initial value
    double volumeMax=0.5;


    //g_value_init(theVol,G_TYPE_DOUBLE);
    g_value_set_double(theVol,volumeMax);
    g_object_set_property(G_OBJECT(volume),"volume",theVol);

    //fade
    long fadeIn,fadeOut, minFade = 500;
    fadeIn = this->track->getFadeInDuration();
    if(fadeIn <= 0 && this->track->getStartTime() > 0)
        fadeIn = minFade;

    fadeOut = this->track->getFadeOutDuration();
    if(fadeOut <= 0 && this->track->getEndTime() > 0)
        fadeOut = minFade;

    if(fadeIn > 10)
        this->setFade(fadeInController,
                  this->track->getStartTime(),
                  this->track->getStartTime()+fadeIn,
                  0.0,volumeMax);

    if(fadeOut > 10)
        if(this->track->getEndTime() > 0)
        this->setFade(fadeOutController,
                  this->track->getEndTime()-fadeOut,
                  this->track->getEndTime(),
                  volumeMax,0.0);


}

// start and end should be expressed in milliseconds
void GstPlayer::setFade(GstController * & controller,long start,long end,double from,double to){
    QLOG_TRACE() << this << "GstPlayer::setFade " << start << " ->" << end << ", "<< from << " -> " << to;
    //g_value_init(theVol,G_TYPE_DOUBLE);

    if(!(controller = gst_controller_new(G_OBJECT(volume),"volume",NULL))){
           QLOG_ERROR() << "Can't get a controller for fade purposes";
           return;
    }
    gst_controller_set_interpolation_mode(controller,"volume",GST_INTERPOLATE_LINEAR);
    g_value_set_double(theVol,from);
    gst_controller_set(controller,"volume",start*GST_MSECOND,theVol);
    g_value_set_double(theVol,to);
    gst_controller_set(controller,"volume",end*GST_MSECOND,theVol);
}

Track * GstPlayer::getTrack(){
    return this->track;
}

void GstPlayer::setTrack(Track * track){
    QLOG_TRACE() << this << "GstPlayer::setTrack";
    this->track = track;
}


void GstPlayer::setUri(const gchar * uri){
    QLOG_TRACE() << this << "Loading URI: "<<uri;
    g_object_set(G_OBJECT(decodebin), "uri", uri, NULL);
}

long GstPlayer::getEndingTime(){
    long ret = track->getEndTime();
    long dur = duration/GST_MSECOND;

    if(dur >= 0){
        if(track->getEndTime() >= 0)
            ret = qMin(dur,track->getEndTime());
        else
            ret =  dur;
    }

    //QLOG_TRACE() << dur << track->getEndTime() << "ret" << ret;
    return ret;
}

void GstPlayer::load(){
    this->buildPipeline();
    QLOG_TRACE() << this << "GstPlayer LOAD";
    GstBus *bus;

    //const char uri = track->getPath();
    QString realPath = "file://"+track->getPath();
    QByteArray byteArray = realPath.toUtf8();
    const gchar * uri = byteArray.data();

    if (uri)
        this->setUri(uri);

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus, GstPlayer::BusCallAsync, this);
    gst_bus_set_sync_handler(bus, GstPlayer::BusCallSync, this);
    gst_object_unref(bus);


    QLOG_TRACE() << "Load finished";
    loaded = true;

    this->requestPause();
}

bool GstPlayer::gstIsInit = false;


int GstPlayer::play()
{
    QLOG_TRACE() << this << "GstPlayer::play";

    //if(!isLoaded){
    GstState state, pending;
    gst_element_get_state(pipeline,&state,&pending,0);
    if(GST_STATE_PAUSED != state){
        QLOG_TRACE() << "Player not ready - can't play. Queueing request.";
        playingRequested = true;
        return 0;
    }

    playingRequested = false;

    if(mustSeek)
        this->seekStart();

    GstStateChangeReturn ret = gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);

    if(GST_STATE_CHANGE_SUCCESS == ret || GST_STATE_CHANGE_NO_PREROLL == ret ){
         QLOG_TRACE() << "Set to play successful.";
    }else if(GST_STATE_CHANGE_ASYNC == ret){ // this is what usually happens when file exists and is being loaded.
        QLOG_TRACE() << "Setting to play asynchronously. Probably all right.";
    }else  if(GST_STATE_CHANGE_FAILURE == ret){
        QLOG_TRACE() << "Failed to change state to PLAY.";
    }

    // start querying position:
    positionQueryTimer->setInterval(500);
    positionQueryTimer->setSingleShot(false);
    connect(positionQueryTimer,SIGNAL(timeout()),this,SLOT(doUpdatePosition()));
    positionQueryTimer->start();

    return 0;
}

void GstPlayer::pause()
{
    positionQueryTimer->stop();
    QLOG_TRACE() << this << "PAUSE";

    GstStateChangeReturn ret = gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED);
    if(GST_STATE_CHANGE_SUCCESS == ret || GST_STATE_CHANGE_NO_PREROLL == ret ){
        QLOG_TRACE() << "Set to pause successful.";
    }else if(GST_STATE_CHANGE_ASYNC == ret){ // this is what usually happens when file exists and is being loaded.
        QLOG_TRACE() << "Setting to pause asynchronously. Probably all right.";
    }else  if(GST_STATE_CHANGE_FAILURE == ret){
        QLOG_TRACE() << "Failed to change state to PAUSE: probably failed to load.";
    }

}


void GstPlayer::doPause(){
    this->pause();
}

void GstPlayer::doStop(){
    this->stop();
}

void GstPlayer::doPlay(){
    this->play();
}

void GstPlayer::doUpdatePosition(){
    gint64 pos;
    if(gst_element_query_position(pipeline,&formatTime,&pos))
        position = pos;

    //int min = position/GST_SECOND/60;
    //int sec = position/GST_SECOND - min*60;
    //QLOG_TRACE() << this << "position:" << min << "m" << sec << "s";

    this->updatePosition(position/GST_MSECOND);
}

void GstPlayer::stop()
{
    this->requestPause();
    this->seekStart();
}

void GstPlayer::seekStart(){
    double start =  ((double)track->getStartTime())*GST_MSECOND;
    double end = ((double)track->getEndTime())*GST_MSECOND;

    bool ok;
    if(0 < end){
        QLOG_TRACE() << "Playing from: "<< start << " to " << end;
        ok = gst_element_seek(pipeline,1,GST_FORMAT_TIME,GST_SEEK_FLAG_FLUSH,
                               GST_SEEK_TYPE_SET,start,
                               GST_SEEK_TYPE_SET, end );
    }else{
        QLOG_TRACE() << "Moving to position: "<< start;
        ok = gst_element_seek_simple(pipeline,GST_FORMAT_TIME,GST_SEEK_FLAG_FLUSH,start);
    }
    QLOG_TRACE() << "Moving result: "<< (ok?"ok":"failed");
    mustSeek = !ok;
}

void GstPlayer::ensureInitGst(){
    if(!gstIsInit){
        gst_init(NULL,NULL);
        gst_controller_init(NULL,NULL);
        gstIsInit = true;
    }
}

GstBusSyncReply GstPlayer::BusCallSync(GstBus *, GstMessage *msg, void *userData)
{
    //QLOG_TRACE() << "Sync bus message" << GST_MESSAGE_TYPE_NAME(msg);
    ((GstPlayer *)userData)->parseMessage(msg);

    return GST_BUS_PASS;

}

gboolean GstPlayer::BusCallAsync(GstBus *, GstMessage *msg, void *userData)
{
    //QLOG_TRACE() << "Async bus message" << GST_MESSAGE_TYPE_NAME(msg);
    ((GstPlayer *)userData)->parseMessage(msg);


    return true;
}


void handleGstTag(const GstTagList * list, const gchar * tag, void * user_data_track){
    gchar * val;
    QString qs_val;
    Track * track = (Track*)user_data_track;

    if( G_TYPE_STRING == gst_tag_get_type(tag) ){
        gst_tag_list_get_string(list,tag,&val);
        //QLOG_TRACE() << " --TAG-- " << tag << " => " << val;

        qs_val = QString(val);
        if( 0 == QString::compare(QString(GST_TAG_ARTIST),QString(tag))){
//            QLOG_TRACE() << "It's an artist";
            track->setArtist(&qs_val);
        }else if (0 == QString::compare(QString(GST_TAG_TITLE),QString(tag))){
//            QLOG_TRACE() << "It's a title";
           track->setTitle(&qs_val);
        }


    }
}




void GstPlayer::handleStateChangeMessage(GstMessage *msg){
    GstState old_state, new_state;

    gst_message_parse_state_changed (msg, &old_state, &new_state, NULL);
    QString objectNamePlayer = gstObjectName;
    if( objectNamePlayer == GST_OBJECT_NAME (msg->src)){

        if(new_state == GST_STATE_PLAYING || old_state == GST_STATE_PLAYING){
            QLOG_TRACE() << "[GST] "<< this <<
                            gst_element_state_get_name (old_state) <<
                            "->"<<  gst_element_state_get_name (new_state);
        }

        switch(new_state){
            case GST_STATE_VOID_PENDING:
                loaded=false;
                playing=false;
                break;
            case GST_STATE_READY:
                loaded=true;
                playing=false;
                break;
            case GST_STATE_NULL:
                loaded=false;
                playing=false;
                break;
            case GST_STATE_PAUSED:
                loaded=true;
                playing=false;
                if(playingRequested){
                    QLOG_TRACE() << "Queued request. Ask to play!";
                    playingRequested = false;
                    this->requestPlay();
                }
                break;
            case GST_STATE_PLAYING:
                loaded=true;
                playing=true;
                break;
        }
        //QLOG_TRACE() << "GstPlayer: emit state change";
        this->stateChanged();
    }
}

void GstPlayer::queryDuration(){
    gint64 len;
    if(gst_element_query_duration(pipeline,&formatTime,&len))
        duration = len;

    int min = duration/GST_SECOND/60;
    int sec = duration/GST_SECOND - min*60;
    QLOG_TRACE() << this << "duration:" << min << "m" << sec << "s";
}

void GstPlayer::parseMessage(GstMessage *msg){
    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_STATE_CHANGED: {
        this->handleStateChangeMessage(msg);
        break;
    }
    case GST_MESSAGE_DURATION:
        this->queryDuration();
        break;
    case GST_MESSAGE_TAG: {
        //QLOG_TRACE() << "[GST]" << GST_MESSAGE_TYPE_NAME(msg);
        GstTagList * tagList;
        // We should merge & store the list each time we get a new tag
        // We should also send a signal for every new tag that is defined
        gst_message_parse_tag(msg,&tagList);
        gst_tag_list_foreach(tagList,handleGstTag,this->track);
        gst_tag_list_free(tagList);
        break;
   }
    case GST_MESSAGE_EOS: {
        QLOG_TRACE() << "[GST] End-of-stream";
        this->requestStop();
        //g_main_loop_quit(loop);
        break;
    }
    case GST_MESSAGE_ERROR: {
        GError *err;
        gst_message_parse_error(msg, &err, NULL);
        QLOG_TRACE() << "[GST] [ERROR] " << err->message;
        error = true;
        g_error_free(err);

        // TODO: handle some errors
        // - Resource not found
        //

       // g_main_loop_quit(loop);
        break;
    }
    default:
        //QLOG_TRACE() << "[GST]" << GST_MESSAGE_TYPE_NAME(msg);
        break;
    }
}


void GstPlayer::handleAddedPad(GstElement * upstream, GstPad * upstreamNewPad, GstElement * downstream) {

  GstPad *downstreamPad = gst_element_get_static_pad ( downstream, "sink");
  GstPadLinkReturn result;
  GstCaps * newPadCaps = NULL;
  GstStructure * newPadStruct = NULL;
  const gchar * newPadType = NULL;

  QLOG_TRACE() << "Got pad " << GST_PAD_NAME (upstreamNewPad) << " from " << GST_ELEMENT_NAME (upstream);

  if (gst_pad_is_linked (downstreamPad)) {
      QLOG_TRACE() << " Pad already connected to downstream.";
  }else{
      newPadCaps = gst_pad_get_caps (upstreamNewPad);
      newPadStruct = gst_caps_get_structure (newPadCaps, 0);
      newPadType = gst_structure_get_name (newPadStruct);

      if (!g_str_has_prefix (newPadType, "audio/x-raw")) {
          QLOG_TRACE() << "Pad is not of type is not raw audio but of type "<< newPadType <<". Can't connect.";
      }else{
          result = gst_pad_link (upstreamNewPad, downstreamPad);
          if (GST_PAD_LINK_FAILED (result)) {
              QLOG_TRACE() << "Failed to link.";
          } else {
              QLOG_TRACE() << "Link successful.";
          }
      }
    }

  if (newPadCaps != NULL)
    gst_caps_unref (newPadCaps);
  gst_object_unref (downstreamPad);
}
