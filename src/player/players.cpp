#include "players.h"

Players::Players(MediaPlayerFactory * playerFactory,QObject *parent) :
    QObject(parent),
    playerFactory(playerFactory),
    playerIdCounter(0)
{
    //players = new QMap<double,IMediaPlayer *>();
    //playersByTrack = new QMap<Track *,QList<double> >();
}


double Players::createPlayer(Track *t){
    double pid = ++playerIdCounter;
    IMediaPlayer * player = playerFactory->getMediaPlayerInstance();
    player->setTrack(t);
    player->load();
    players.insert(pid,player);
    if(!playersByTrack.contains(t)){
        playersByTrack.insert(t,new QList<double>());
    }
    (playersByTrack.value(t))->append(pid);
}

IMediaPlayer * Players::getPlayer(double playerId){
    return players.value(playerId);
}

QList<double> *  Players::getPlayers(Track * t){
    return playersByTrack.value(t);
}

void Players::stopAll(){
    foreach (IMediaPlayer * player, players.values()) {
        player->stop();
    }
}

void Players::stopAllForTrack(Track *t){
    foreach (double pid, *playersByTrack.value(t)) {
        players.value(pid)->stop();
    }
}

