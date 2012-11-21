#ifndef MAINTESTS_H
#define MAINTESTS_H

#include "QsLog.h"
#include "QsLogDest.h"
#include <gst/gst.h>
#include <gst/controller/gstcontroller.h>
#include "player/gst/gstplayer.h"

class AdvGstPlayer;
void pad_added_handler (GstElement *src, GstPad *new_pad, AdvGstPlayer *data);


class AdvGstPlayer: public GstPlayer{

public:
    AdvGstPlayer(QObject *parent = 0):GstPlayer(parent){
        QLOG_TRACE() << "AdvGstPlayer CREATE";
        gst_controller_init(NULL,NULL);
    }

    virtual ~AdvGstPlayer(){
        QLOG_TRACE() << "AdvGstPlayer DELETE";
    }
    GstElement * elem2;
protected:
    GstElement * decodebin;
    GstElement * audiobin;
    GstElement * elem1;
    GstPad  * pad1;
    GstPad * pad2;
    GstController * ctrl;
    GValue vol;

    virtual void setUri(const gchar * uri){
        g_object_set(G_OBJECT(decodebin), "uri", uri, NULL);
    }

    virtual void buildPipeline(){
        QLOG_TRACE() << "AdvGstPlayer::buildPipeline";

        pipeline = gst_element_factory_make("pipeline", "player");

        decodebin = gst_element_factory_make("uridecodebin",NULL);

        audiobin = gst_element_factory_make("autoaudiosink",NULL);

        //elem1 = gst_element_factory_make("queue2",NULL);
        elem2 = gst_element_factory_make("audioconvert",NULL);


        gst_bin_add(GST_BIN(pipeline), decodebin);
        //gst_bin_add(GST_BIN(pipeline), elem1);
        gst_bin_add(GST_BIN(pipeline), elem2);
        gst_bin_add(GST_BIN(pipeline), audiobin);

        gst_element_link(elem2, audiobin);

        /* Connect to the pad-added signal */
        g_signal_connect (decodebin, "pad-added", G_CALLBACK (pad_added_handler), this);
/*
        bin = gst_bin_new("inbin");

        //elem1 = gst_element_factory_make("equalizer-10bands",NULL);
        elem2 = gst_element_factory_make("autoaudiosink",NULL);

        gst_bin_add(GST_BIN (bin), elem2);
        //gst_bin_add_many(GST_BIN (bin), elem1,elem2, NULL);

        pad1 = gst_element_get_pad(elem2,"sink");

        pad2 = gst_ghost_pad_new("gpad",pad1);

        gst_element_add_pad(bin,pad2);*/

/*
        if(!(ctrl = gst_controller_new(G_OBJECT(pipeline),"volume",NULL))){
               QLOG_ERROR() << "Can't control";
               exit(0);
        }

        gst_controller_set_interpolation_mode(ctrl,"volume",GST_INTERPOLATE_LINEAR);*/

        //vol;
/*
        g_value_init(&vol,G_TYPE_DOUBLE);

        g_value_set_double(&vol,0.0);
        gst_controller_set(ctrl,"volume",0*GST_SECOND,&vol);

        g_value_set_double(&vol,1.0);
        gst_controller_set(ctrl,"volume",5*GST_SECOND,&vol);

        g_value_set_double(&vol,220.0);
        gst_controller_set(ctrl,"freq",0*GST_SECOND,&vol);

        g_value_set_double(&vol,3520.0);
        gst_controller_set(ctrl,"freq",3*GST_SECOND,&vol);

        g_value_set_double(&vol,440.0);
        gst_controller_set(ctrl,"freq",6*GST_SECOND,&vol);*/


        //gst_element_link(pipeline,bin);
    }
};

void pad_added_handler (GstElement *src, GstPad *new_pad, AdvGstPlayer *data) {
  GstPad *sink_pad = gst_element_get_static_pad (data->elem2, "sink");
  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("  We are already linked. Ignoring.\n");
    goto exit;
  }

  /* Check the new pad's type */
  new_pad_caps = gst_pad_get_caps (new_pad);
  new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
  new_pad_type = gst_structure_get_name (new_pad_struct);
  if (!g_str_has_prefix (new_pad_type, "audio/x-raw")) {
    g_print ("  It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
    goto exit;
  }

  /* Attempt the link */
  ret = gst_pad_link (new_pad, sink_pad);
  if (GST_PAD_LINK_FAILED (ret)) {
    g_print ("  Type is '%s' but link failed.\n", new_pad_type);
  } else {
    g_print ("  Link succeeded (type '%s').\n", new_pad_type);
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}


void testGstreamer(){
    QLOG_TRACE() << "Create player";
    AdvGstPlayer * player = new AdvGstPlayer();
    Track * t = new Track(
                "/home/jehan/Perso/sons/ExemplesMusicImpro/Anastacia - I Do (Feat. Sonny From P.O.D.).mp3"
                ,false,30000,-1,0,0,false);

    player->setTrack(t);
    player->load();

    sleep(1);

    player->play();

    sleep(5);

    player->stop();

    sleep(1);

    QLOG_TRACE() << "The end";
    delete player;
    delete t;
}


#endif // MAINTESTS_H
