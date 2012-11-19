#ifndef GSTPLAYER_H
#define GSTPLAYER_H

#include <QThread>
#include "QsLog.h"
#include "QsLogDest.h"
#include <gst/gst.h>
#include "track.h"
#include "imediaplayer.h"
#include "imediaplayerwatcher.h"



class GstPlayer : public QObject, public IMediaPlayer
{
    Q_OBJECT
public:
    GstPlayer(QObject *parent = 0);
    ~GstPlayer(){
        if(pipeline)
            delete pipeline;
    }

    //void run();


    void load();
    int play();
    void pause();
    void stop();

    // TODO
    Track * getTrack();
    void setTrack(Track * track);
    //void setUri(const char *);
    bool isPlaying(){return playing;}
    bool isLoaded(){return loaded;}
    bool hasError(){return error;}
    //void print(){}
    //const char * getUri() const {return NULL;}



private:


    // IMediaPlayerWatcher * watcher;
    Track * track;
    //QString uri;
    bool playing;
    bool loaded;
    bool error;
    GstElement *pipeline;
    void parseMessage(GstMessage *msg);


     // this does not belong to the player I think. Move to a GstEngine class?
    static bool gstIsInit;
    static void ensureInitGst();
    static GstBusSyncReply BusCallSync(GstBus *bus, GstMessage *msg, void *user_data);
    static gboolean BusCallAsync(GstBus *bus, GstMessage *msg, void *user_data);

signals:
        void requestPause();
        void requestStop();
        void requestPlay();

private slots:
        void doPause();
        void doStop();
        void doPlay();


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
