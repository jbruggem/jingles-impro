#include "playerwrapper.h"

PlayerWrapper::PlayerWrapper(MediaPlayerFactory * playerFactory,QObject *parent) :
    QObject(parent),
    playerFactory(playerFactory)
{
    players = QMap<Track *,TrackPlayer *>();
}


void PlayerWrapper::load(Track *t){
    if(!players.contains(t)){
        players.insert(t,new TrackPlayer(t,playerFactory, this));
    }
}

void PlayerWrapper::stopAll(Track *t){
    if(!players.contains(t)){
        QLOG_FATAL() << "Can't stop track: not loaded.";
        return;
    }

    players.value(t)->stopAll();
}


void PlayerWrapper::play(Track *t){
    if(!players.contains(t)){
        this->load(t);
    }

    players.value(t)->playNew();
}
