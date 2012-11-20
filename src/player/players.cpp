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
    connect(player,SIGNAL(stateChanged()),this,SLOT(playerStateChanged()));
    player->setTrack(t);
    player->load();
    players.insert(pid,player);
    if(!playersByTrack.contains(t)){
        playersByTrack.insert(t,new QList<int>());
    }
    (playersByTrack.value(t))->append(pid);
    return pid;
}

void Players::playerStateChanged(){
    bool playing;
    // This sucks big time.
    // It's a clear sign this whole chain of objects
    // should be rethought thoroughly.

    //QLOG_TRACE() << "Players::playerStateChanged ";
    foreach(Track * t,playersByTrack.keys()){
        playing = false;
        foreach (int pid, *playersByTrack.value(t)) {
            playing |= players.value(pid)->isPlaying();
        }
       // QLOG_TRACE() << "Update " << t << " "<< playing;
        this->playingStateChange(t,playing);
    }

}

IMediaPlayer * Players::getPlayer(int playerId){
    QLOG_TRACE() << "Players::getPlayer " << playerId;
    QLOG_TRACE() << "Current players: "<< players.keys();
    if(players.contains(playerId))
        return players.value(playerId);
    else
        return NULL;
}

IMediaPlayer * Players::getAvailablePlayer(Track * t){
    IMediaPlayer * player = 0;
    IMediaPlayer * tmpPlayer;

    foreach (int pid, *playersByTrack.value(t)) {
        tmpPlayer = players.value(pid);
        if(tmpPlayer->hasError()){
            QLOG_TRACE() << "[players] remove erro'd player " << tmpPlayer;
            removePlayer(pid);
        }else if(tmpPlayer->isLoaded() && !tmpPlayer->isPlaying()){
            QLOG_TRACE() << "[players] found adequate player " << tmpPlayer;
            player = tmpPlayer;
            break;
        }
    }

    if(!player){ // no free player. Make a new one
        QLOG_TRACE() << "[players] no free player. Creating.";
        player = players.value(this->createPlayer(t));
    }

    return player;
}

QList<int> *  Players::getPlayers(Track * t){
    return playersByTrack.value(t);
}

void Players::stopAll(){
    foreach (IMediaPlayer * player, players.values()) {
        player->stop();
    }
}

void Players::removePlayer(int pid){
    IMediaPlayer * player = players.value(pid);
    players.remove(pid);
    playersByTrack.value(player->getTrack())->removeOne(pid);
    delete player;
}

void Players::stopAllForTrack(Track *t){
    QLOG_TRACE() << "stopAllForTrack " << t->getPath() ;

    foreach (int pid, *playersByTrack.value(t)) {
        QLOG_TRACE() << "Stop player " << pid;
        IMediaPlayer * player = players.value(pid);
        player->stop();
        //players.remove(pid);
        //playersByTrack.value(t)->removeOne(pid);
        //delete player;
    }
}

