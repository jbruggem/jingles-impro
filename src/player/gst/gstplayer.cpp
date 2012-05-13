#include "gstplayer.h"

GstPlayer::GstPlayer(QObject *parent):
    QObject(parent)
{
    GstPlayer::ensureInitGst();
    //watcher = NULL;
    pipeline = gst_element_factory_make("playbin2", "player");
}

/*
void GstPlayer::run(){
    QLOG_TRACE() << "PlayThread Start play";
    play();
}*/

void GstPlayer::setTrack(Track * track){
    this->track = track;
}


void GstPlayer::load(){
    QLOG_TRACE() << "LOAD";
    GstBus *bus;

    //const char uri = track->getPath();
    QString realPath = "file://"+*track->getPath();
    QByteArray byteArray = realPath.toLocal8Bit();
    const gchar * uri = byteArray.data();

    if (uri)
        g_object_set(G_OBJECT(pipeline), "uri", uri, NULL);

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus, GstPlayer::BusCallAsync, this);
    gst_bus_set_sync_handler(bus, GstPlayer::BusCallSync, this);

    gst_object_unref(bus);
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED);


    isLoaded = true;
}

bool GstPlayer::gstIsInit = false;


int GstPlayer::play()
{
    QLOG_TRACE() << "GstPlayer::play";

    if(!isLoaded){
        QLOG_TRACE() << "Nothing loaded - can't play";
        return 1;
    }



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
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);

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
    QLOG_TRACE() << "PAUSE";

    if(!isLoaded){
        QLOG_TRACE() << "Nothing loaded - can't pause";
        return;
    }

    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED);
    return;
}

void GstPlayer::stop()
{
    QLOG_TRACE() << "stop";

    if(!isLoaded){
        QLOG_TRACE() << "Nothing loaded - can't stop";
        return;
    }

    /*if(watcher){
        watcher->terminate();
        delete watcher;
        watcher = NULL;
    }*/
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED);

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
        //QLOG_TRACE() << "[GST] "<< GST_OBJECT_NAME (msg->src) <<": " <<  gst_element_state_get_name (old_state) <<"->"<<  gst_element_state_get_name (new_state);

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
        g_message("End-of-stream");
        //g_main_loop_quit(loop);
        break;
    }
    case GST_MESSAGE_ERROR: {
        GError *err;
        gst_message_parse_error(msg, &err, NULL);
        g_error("%s", err->message);
        g_error_free(err);

       // g_main_loop_quit(loop);
        break;
    }
    default:
        //QLOG_TRACE() << "[GST]" << GST_MESSAGE_TYPE_NAME(msg);
        break;
    }
}
