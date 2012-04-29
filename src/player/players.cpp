#include "playerwrapper.h"

Players::Players(MediaPlayerFactory * playerFactory,QObject *parent) :
    QObject(parent),
    playerFactory(playerFactory)
{
    players = QMap<Track *,TrackPlayer *>();
}


void Players::load(Track *t){
    if(!players.contains(t)){
        players.insert(t,new TrackPlayer(t,playerFactory, this));
    }
}

void Players::stopAll(Track *t){
    if(!players.contains(t)){
        QLOG_FATAL() << "Can't stop track: not loaded.";
        return;
    }

    players.value(t)->stopAll();
}


void Players::play(Track *t){
    if(!players.contains(t)){
        this->load(t);
    }

    players.value(t)->playNew();
}
