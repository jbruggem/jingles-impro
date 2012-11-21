#include "gstplayer.h"

GstPlayer::GstPlayer(QObject *parent):
    IMediaPlayer(parent),
    playing(false),
    loaded(false),
    error(false),
    pipeline(0),
    gstObjectName("player")
{
    GstPlayer::ensureInitGst();
    connect(this,SIGNAL(requestPause()),this,SLOT(doPause()));
    connect(this,SIGNAL(requestPlay()),this,SLOT(doPlay()));
    connect(this,SIGNAL(requestStop()),this,SLOT(doStop()));
    //watcher = NULL;
    pipeline = gst_element_factory_make("playbin2", gstObjectName);
}

/*
void GstPlayer::run(){
    QLOG_TRACE() << "PlayThread Start play";
    play();
}*/

Track * GstPlayer::getTrack(){
    return this->track;
}

void GstPlayer::setTrack(Track * track){
    QLOG_TRACE() << this << "GstPlayer::setTrack";
    this->track = track;
}


void GstPlayer::load(){
    QLOG_TRACE() << this << "GstPlayer LOAD";
    GstBus *bus;

    //const char uri = track->getPath();
    QString realPath = "file://"+track->getPath();
    QByteArray byteArray = realPath.toUtf8();
    const gchar * uri = byteArray.data();

    if (uri)
        g_object_set(G_OBJECT(pipeline), "uri", uri, NULL);

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
            QLOG_TRACE() << "Nothing loaded - can't play";
            return 1;
        }
    //}

    double start =  ((double)track->getStartTime())*GST_MSECOND;
    double end = ((double)track->getEndTime())*GST_MSECOND;

    bool ok;
    if(0 < end){
        QLOG_TRACE() << "Looping from: "<< start << " to " << end;
        ok = gst_element_seek(pipeline,1,GST_FORMAT_TIME,GST_SEEK_FLAG_FLUSH,
                               GST_SEEK_TYPE_SET,start,
                               GST_SEEK_TYPE_SET, end );
    }else{
        QLOG_TRACE() << "Moving to position: "<< start;
        ok = gst_element_seek_simple(pipeline,GST_FORMAT_TIME,GST_SEEK_FLAG_FLUSH,start);
    }
    QLOG_TRACE() << "Moving result: "<< (ok?"ok":"failed");

    gint64 position = 0;
    GstFormat format = GST_FORMAT_TIME;
    gst_element_query_position(pipeline,&format,&position);

    QLOG_TRACE() << "Position before playing is: "<< position;
    GstStateChangeReturn ret = gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
    if(GST_STATE_CHANGE_SUCCESS == ret || GST_STATE_CHANGE_NO_PREROLL == ret ){
         QLOG_TRACE() << "Set to play successful.";
    }else if(GST_STATE_CHANGE_ASYNC == ret){ // this is what usually happens when file exists and is being loaded.
        QLOG_TRACE() << "Setting to play asynchronously. Probably all right.";
    }else  if(GST_STATE_CHANGE_FAILURE == ret){
        QLOG_TRACE() << "Failed to change state to PLAY.";
    }

    //sleep(1);

   /* double start =  ((double)track->getStartTime())*GST_MSECOND;
    double end = ((double)track->getEndTime())*GST_MSECOND;

    QLOG_TRACE() << "Looping from: "<< start << " to " << end;
    gst_element_seek(pipeline,1.0,GST_FORMAT_TIME,GST_SEEK_FLAG_FLUSH,
                               GST_SEEK_TYPE_SET, start,
                               GST_SEEK_TYPE_SET, end);*/
   /* if( track->getEndTime() > 0 ){
        // find the time it should actually play
        gint64 position = 0;
        GstFormat format = GST_FORMAT_TIME;
        gst_element_query_position(pipeline,&format,&position);

        QLOG_TRACE() << "Position before playing is: "<< position;

        int duration = track->getEndTime() - position;

        if(0 < duration){
            // set the watcher thread to stop this player appropriately
            watcher = new IMediaPlayerWatcher(this, duration, this);
            watcher->start();
            QLOG_TRACE() << "Setting a watcher for duration: "<< duration ;
            gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
        }else{
            QLOG_WARN() << "Could not continue playing. Current position ("<< position <<") bigger or equal to track's endTime ("<< track->getEndTime() <<").";
        }
    }else{
        QLOG_TRACE() << "No need for watcher - endTime < 0.";
    }*/
    return 0;
}

void GstPlayer::pause()
{
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


void GstPlayer::stop()
{
    QLOG_TRACE() << this << "STOP";
/*
    if(!isLoaded){
        QLOG_TRACE() << "Nothing loaded - can't stop";
        return;
    }*/

    /*if(watcher){
        watcher->terminate();
        delete watcher;
        watcher = NULL;
    }*/
    this->requestPause();

    gint64 position = 0;
    GstFormat format = GST_FORMAT_TIME;

    gst_element_query_position(pipeline,&format,&position);
}

void GstPlayer::ensureInitGst(){
    if(!gstIsInit){
        gst_init(NULL,NULL);
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

void GstPlayer::parseMessage(GstMessage *msg){
    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_STATE_CHANGED: {
        GstState old_state, new_state;

        gst_message_parse_state_changed (msg, &old_state, &new_state, NULL);
        QString objectNamePlayer = gstObjectName;
        if( objectNamePlayer == GST_OBJECT_NAME (msg->src)){
            QLOG_TRACE() << "[GST] "<< this << /*this->track->getFilename() <<*/ ": " << gst_element_state_get_name (old_state) <<"->"<<  gst_element_state_get_name (new_state);
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
                    break;
                case GST_STATE_PLAYING:
                    loaded=true;
                    playing=true;
                    break;
            }
            //QLOG_TRACE() << "GstPlayer: emit state change";
            this->stateChanged();
        }
        break;
    }
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
