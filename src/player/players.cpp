#include "players.h"

Players::Players(MediaPlayerFactory * playerFactory,QObject *parent) :
    QObject(parent),
    playerFactory(playerFactory),
    playerIdCounter(0)
{
    //players = new QMap<double,IMediaPlayer *>();
    //playersByTrack = new QMap<Track *,QList<double> >();
}



void Players::ensureTrackExists(Track *t){
    if(!playersByTrack.contains(t)){
        playersByTrack.insert(t,new QList<int>());
    }
}


int Players::createPlayer(Track *t){
    QLOG_TRACE() << "Players::createPlayer";
//    int playing;

//    foreach (int pid, *playersByTrack.value(t)) {
//        playing += players.value(pid)->isPlaying();
//    }

    if((*playersByTrack.value(t)).size() > MAX_NUM_PLAYERS){
        QLOG_WARN() << "Players::createPlayer: can't have more than "<< MAX_NUM_PLAYERS <<" players.";
        QLOG_TRACE() << "Total players: " << players.size();
        QLOG_TRACE() << "This track: " << (*playersByTrack.value(t)).size();
        return -1;
    }
    ensureTrackExists(t);
    int pid = ++playerIdCounter;
    IMediaPlayer * player = playerFactory->getMediaPlayerInstance();
    connect(player,SIGNAL(stateChanged()),this,SLOT(playerStateChanged()));
    player->setTrack(t);
    player->load();
    players.insert(pid,player);
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
    ensureTrackExists(t);

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
        int pid  = this->createPlayer(t);
        if(0 <= pid)
            player = players.value(pid);
        else
            return NULL;
    }

    return player;
}

QList<int> *  Players::getPlayers(Track * t){
    ensureTrackExists(t);
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
    ensureTrackExists(t);
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

