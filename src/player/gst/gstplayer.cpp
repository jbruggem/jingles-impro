#include "gstplayer.h"

GstPlayer::GstPlayer(){
    GstPlayer::ensureInitGst();

    pipeline = gst_element_factory_make("playbin2", "player");
}


void GstPlayer::run(){
    QLOG_TRACE() << "PlayThread Start play";
    play();
}

void GstPlayer::load(Track * track){
    QLOG_TRACE() << "LOAD";
    GstBus *bus;

    //const char uri = track->getPath();
    QString realPath = "file://"+*track->getPath();
    QByteArray byteArray = realPath.toLocal8Bit();
    const gchar * uri = byteArray.data();

    if (uri)
        g_object_set(G_OBJECT(pipeline), "uri", uri, NULL);

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus, GstPlayer::BusCallAsync, NULL);
    gst_bus_set_sync_handler(bus, GstPlayer::BusCallSync, NULL);

    gst_object_unref(bus);
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED);

    isLoaded = true;
}

bool GstPlayer::gstIsInit = false;


void GstPlayer::play()
{
    QLOG_TRACE() << "PLAY";

    if(!isLoaded){
        QLOG_TRACE() << "Nothing loaded - can't play";
        return;
    }

    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
}

void GstPlayer::stop()
{
    QLOG_TRACE() << "stop";

    if(!isLoaded){
        QLOG_TRACE() << "Nothing loaded - can't stop";
        return;
    }

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

GstBusSyncReply GstPlayer::BusCallSync(GstBus *bus, GstMessage *msg, void *user_data)
{
    QLOG_TRACE() << "Sync bus message" << GST_MESSAGE_TYPE_NAME(msg);
    parseMessage(msg);

    return GST_BUS_PASS;

}

gboolean GstPlayer::BusCallAsync(GstBus *bus, GstMessage *msg, void *user_data)
{
    QLOG_TRACE() << "Async bus message" << GST_MESSAGE_TYPE_NAME(msg);
    parseMessage(msg);


    return true;
}

void parseMessage(GstMessage *msg){

    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_STATE_CHANGED: {
        GstState old_state, new_state;

        gst_message_parse_state_changed (msg, &old_state, &new_state, NULL);
        QLOG_TRACE() << "Element"<< GST_OBJECT_NAME (msg->src) <<" changed state from " <<  gst_element_state_get_name (old_state) <<" to "<<  gst_element_state_get_name (new_state) << ".\n";

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
        break;
    }
}
