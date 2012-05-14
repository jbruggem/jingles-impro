#include "players.h"

Players::Players(MediaPlayerFactory * playerFactory,QObject *parent) :
    QObject(parent),
    playerFactory(playerFactory),
    playerIdCounter(0)
{
    //players = new QMap<double,IMediaPlayer *>();
    //playersByTrack = new QMap<Track *,QList<double> >();
}


int Players::createPlayer(Track *t){
    QLOG_TRACE() << "Players::createPlayer";
    int pid = ++playerIdCounter;
    IMediaPlayer * player = playerFactory->getMediaPlayerInstance();
    player->setTrack(t);
    player->load();
    players.insert(pid,player);
    if(!playersByTrack.contains(t)){
        playersByTrack.insert(t,new QList<int>());
    }
    (playersByTrack.value(t))->append(pid);
    return pid;
}

IMediaPlayer * Players::getPlayer(int playerId){
    QLOG_TRACE() << "Players::getPlayer " << playerId;
    QLOG_TRACE() << "Current players: "<< players.keys();
    if(players.contains(playerId))
        return players.value(playerId);
    else
        return NULL;
}

QList<int> *  Players::getPlayers(Track * t){
    return playersByTrack.value(t);
}

void Players::stopAll(){
    foreach (IMediaPlayer * player, players.values()) {
        player->stop();
    }
}

void Players::stopAllForTrack(Track *t){
    QLOG_TRACE() << "stopAllForTrack " << t->getPath() ;

    foreach (int pid, *playersByTrack.value(t)) {
        QLOG_TRACE() << "Stop player " << pid;
        IMediaPlayer * player = players.value(pid);
        player->stop();
        players.remove(pid);
        playersByTrack.value(t)->removeOne(pid);
        delete player;
    }
}

