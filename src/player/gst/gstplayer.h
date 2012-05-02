#ifndef GSTPLAYER_H
#define GSTPLAYER_H

#include <QThread>
#include "QsLog.h"
#include "QsLogDest.h"
#include <gst/gst.h>
#include "track.h"
#include "imediaplayer.h"


class GstPlayer : /*public QThread, */public IMediaPlayer
{
public:
    GstPlayer();
    //void run();


    void load();
    int play();
    void pause();
    void stop();

    // TODO
    void setTrack(Track * track);
    //void setUri(const char *);
    bool isPlaying(){return true;}
    //void print(){}
    //const char * getUri() const {return NULL;}



private:
    Track * track;
    //QString uri;
    GstElement *pipeline;
    bool isLoaded;
    void parseMessage(GstMessage *msg);

     // this does not belong to the player I think. Move to a GstEngine class?
    static bool gstIsInit;
    static void ensureInitGst();
    static GstBusSyncReply BusCallSync(GstBus *bus, GstMessage *msg, void *user_data);
    static gboolean BusCallAsync(GstBus *bus, GstMessage *msg, void *user_data);

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
