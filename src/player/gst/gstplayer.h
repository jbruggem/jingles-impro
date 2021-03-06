#ifndef GSTPLAYER_H
#define GSTPLAYER_H

#include <QThread>
#include <QTimer>
#include "QsLog.h"
#include "QsLogDest.h"
#include <gst/gst.h>
#include <gst/controller/gstcontroller.h>
#include "track.h"
#include "imediaplayer.h"
#include "imediaplayerwatcher.h"



class GstPlayer : public IMediaPlayer
{
    Q_OBJECT
public:
    GstPlayer(QObject *parent = 0);
    virtual ~GstPlayer(){
        QLOG_TRACE() << "GstPlayer DELETE";
        if(pipeline)
            gst_object_unref(pipeline);
        if(audioconvert)
            gst_object_unref(audioconvert);
        if(volume)
            gst_object_unref(volume);
        if(decodebin)
            gst_object_unref(decodebin);
        if(audiobin)
            gst_object_unref(audiobin);
        if(fadeInController)
            gst_object_unref(fadeInController);
        if(fadeOutController)
            gst_object_unref(fadeOutController);
        delete theVol;
    }


    void load();
    int play();
    void pause();
    void stop();
    long getEndingTime();

    // TODO
    Track * getTrack();
    void setTrack(Track * track);
    //void setUri(const char *);
    bool isPlaying(){return playing;}
    bool isLoaded(){return loaded;}
    bool hasError(){return error;}
    //void print(){}
    //const char * getUri() const {return NULL;}

signals:
        void stateChanged();

private:
        void seekStart();
        void buildPipeline();
        void setUri(const gchar * uri);
        void setFade(GstController * & controller,long start,long end,double from,double to);
        Track * track;
        bool playing;
        bool loaded;
        bool error;
        bool playingRequested;
        bool mustSeek;
        long duration;
        long position;
        GstFormat formatTime;
        GstElement *pipeline;
        QString gstObjectName;
        GstElement * decodebin;
        GstElement * audiobin;
        GstController * fadeInController;
        GstController * fadeOutController;
        GstElement * audioconvert;
        GstElement * volume;
        GValue * theVol;
        QTimer * positionQueryTimer;

    // IMediaPlayerWatcher * watcher;
    //QString uri;
    void parseMessage(GstMessage *msg);
    void handleStateChangeMessage(GstMessage *msg);
    void queryDuration();



     // this does not belong to the player I think. Move to a GstEngine class?
    static bool gstIsInit;
    static void ensureInitGst();
    static gboolean runGetPosition(GstPlayer * player);
    static GstBusSyncReply BusCallSync(GstBus *bus, GstMessage *msg, void *user_data);
    static gboolean BusCallAsync(GstBus *bus, GstMessage *msg, void *user_data);
    static void handleAddedPad(GstElement * upstream, GstPad * upstreamNewPad, GstElement * downstream);

signals:
        void requestPause();
        void requestStop();
        void requestPlay();
        void updatePosition(long position);

private slots:
        void doPause();
        void doStop();
        void doPlay();
        void doUpdatePosition();


};

/*GstElement * getPipeline(){
   return pipeline;
}*/
/*
#include "mediaplayerinterface.h"
class GstPlayer : public MediaPlayerInterface
{
public:
    GstPlayer();
};
*/
#endif // GSTPLAYER_H
