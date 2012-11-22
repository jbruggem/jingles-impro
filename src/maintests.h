#ifndef MAINTESTS_H
#define MAINTESTS_H

#include "QsLog.h"
#include "QsLogDest.h"
#include <gst/gst.h>
#include <gst/controller/gstcontroller.h>
#include "player/gst/gstplayer.h"

class AdvGstPlayer;
void pad_added_handler (GstElement *src, GstPad *new_pad, GstElement *data);


class AdvGstPlayer: public GstPlayer{

public:
    AdvGstPlayer(QObject *parent = 0):
        GstPlayer(parent)
    {
        QLOG_TRACE() << "AdvGstPlayer CREATE";
        gst_controller_init(NULL,NULL);
    }

    virtual ~AdvGstPlayer(){
        QLOG_TRACE() << "AdvGstPlayer DELETE";
        gst_object_unref(audioconvert);
        gst_object_unref(volume);
        gst_object_unref(decodebin);
        gst_object_unref(audiobin);
        gst_object_unref(fadeInController);
        gst_object_unref(fadeOutController);
    }
    GstElement * audioconvert;
    GstElement * volume;
protected:
    GstElement * decodebin;
    GstElement * audiobin;
    GstController * fadeInController;
    GstController * fadeOutController;
    GValue * theVol;

    virtual void setUri(const gchar * uri){
        g_object_set(G_OBJECT(decodebin), "uri", uri, NULL);
    }

    virtual void buildPipeline(){
        QLOG_TRACE() << "AdvGstPlayer::buildPipeline";

        pipeline = gst_element_factory_make("pipeline", "player");

        decodebin = gst_element_factory_make("uridecodebin",NULL);


        //elem1 = gst_element_factory_make("queue2",NULL);
        audioconvert = gst_element_factory_make("audioconvert",NULL);
        volume = gst_element_factory_make("volume",NULL);

        audiobin = gst_element_factory_make("autoaudiosink",NULL);


        gst_bin_add(GST_BIN(pipeline), decodebin);
        //gst_bin_add(GST_BIN(pipeline), elem1);
        gst_bin_add(GST_BIN(pipeline), audioconvert);
        gst_bin_add(GST_BIN(pipeline), volume);
        gst_bin_add(GST_BIN(pipeline), audiobin);

        gst_element_link_many(volume, audioconvert, audiobin, NULL);

        /* Connect to the pad-added signal */
        g_signal_connect (decodebin, "pad-added", G_CALLBACK (pad_added_handler), volume);
/*
        bin = gst_bin_new("inbin");

        //elem1 = gst_element_factory_make("equalizer-10bands",NULL);
        elem2 = gst_element_factory_make("autoaudiosink",NULL);

        gst_bin_add(GST_BIN (bin), elem2);
        //gst_bin_add_many(GST_BIN (bin), elem1,elem2, NULL);

        pad1 = gst_element_get_pad(elem2,"sink");

        pad2 = gst_ghost_pad_new("gpad",pad1);

        gst_element_add_pad(bin,pad2);*/


        //GValue * vol = theVol;
        theVol = new GValue();
        g_value_init(theVol,G_TYPE_DOUBLE);
       /* g_value_set_double(vol,0.01);
        g_object_set_property(G_OBJECT(volume),"volume",vol);*/

        if(!(fadeInController = gst_controller_new(G_OBJECT(volume),"volume",NULL))){
               QLOG_ERROR() << "Can't control";
               return;
        }

        gst_controller_set_interpolation_mode(fadeInController,"volume",GST_INTERPOLATE_CUBIC);


        g_value_set_double(theVol,0.0);
        gst_controller_set(fadeInController,"volume",30*GST_SECOND,theVol);

        g_value_set_double(theVol,1.0);
        gst_controller_set(fadeInController,"volume",31*GST_SECOND,theVol);

        if(!(fadeOutController = gst_controller_new(G_OBJECT(volume),"volume",NULL))){
               QLOG_ERROR() << "Can't control";
               return;
        }

        gst_controller_set_interpolation_mode(fadeOutController,"volume",GST_INTERPOLATE_CUBIC);


        g_value_set_double(theVol,1.0);
        gst_controller_set(fadeOutController,"volume",38*GST_SECOND,theVol);

        g_value_set_double(theVol,0.0);
        gst_controller_set(fadeOutController,"volume",40*GST_SECOND,theVol);


//*/


        //gst_element_link(pipeline,bin);
    }
};

void pad_added_handler (GstElement * upstream, GstPad * upstreamNewPad, GstElement * downstream) {

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

    sleep(10);

    player->stop();

    sleep(1);

    QLOG_TRACE() << "The end";
    delete player;
    delete t;
}


#endif // MAINTESTS_H
