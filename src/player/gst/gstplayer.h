#ifndef GSTPLAYER_H
#define GSTPLAYER_H

#include "mediaplayerinterface.h"
/*
class GstPlayer : public MediaPlayerInterface
{
public:
    GstPlayer();
};
*/
#include <gst/gst.h>


class GstPlayer : public QThread
{
public:
    GstPlayer(){
        gst_init(NULL,NULL);
        pipeline = gst_element_factory_make("playbin2", "player");
    }


    void run(){
        QLOG_TRACE() << "PlayThread Start play_uri";
        play_uri("file:///home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 10 Le vaste espace.mp3");
        QLOG_TRACE() << "PlayThread End play_uri";
    }

    GstElement * getPipeline(){
       return pipeline;
    }

    GstElement *pipeline;

    void play_uri(const char *uri)
    {
        GstBus *bus;
        //GMainLoop * loop = g_main_loop_new(NULL, FALSE);

        if (uri)
            g_object_set(G_OBJECT(pipeline), "uri", uri, NULL);

        bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
        gst_bus_add_watch(bus, PlayThread::bus_call, NULL);
        gst_bus_set_sync_handler(bus, PlayThread::bus_call_sync, NULL);

        gst_object_unref(bus);

        gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
        //g_main_loop_run(loop);

         //gst_element_query_position()


        //gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
        //gst_object_unref(GST_OBJECT(pipeline));
    }

    static GstBusSyncReply bus_call_sync(GstBus *bus, GstMessage *msg, void *user_data)
    {
        QLOG_TRACE() << "Sync bus message" << GST_MESSAGE_TYPE_NAME(msg);
        return GST_BUS_PASS;

    }

    static gboolean bus_call(GstBus *bus, GstMessage *msg, void *user_data)
    {
        QLOG_TRACE() << "Async bus message" << GST_MESSAGE_TYPE_NAME(msg);


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

        return true;
    }

};

#endif // GSTPLAYER_H
