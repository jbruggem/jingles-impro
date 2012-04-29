#ifndef GSTPLAYER_H
#define GSTPLAYER_H

#include <QThread>
#include "QsLog.h"
#include "QsLogDest.h"
#include <gst/gst.h>
#include "track.h"

void parseMessage(GstMessage *msg);

class GstPlayer : public QThread
{
public:
    GstPlayer();
    void run();
    void load(Track * track);
    void play();
    void stop();

private:
    GstElement *pipeline;
    bool isLoaded;
    static bool gstIsInit;
     // this does not belong to the player I think. Move to a GstEngine class?
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
