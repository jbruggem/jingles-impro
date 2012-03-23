#include "trackplayer.h"

TrackPlayer::TrackPlayer(Track * track,MediaPlayerFactory * factory,QObject *parent) :
    QObject(parent),
    track(track),
    playerFactory(factory)
{
    this->provisionPlayer();
}

void TrackPlayer::provisionPlayer(){
    QLOG_TRACE << "Provisionning media player";
    mediaplayers.append(playerFactory->getMediaPlayerInstance());

}

void TrackPlayer::playNew(){
    QLOG_TRACE << "TrackPlayer playNew";
    mediaplayers.last()->play();
    this->provisionPlayer();
}

void TrackPlayer::stopAll(){
    QLOG_TRACE << "TrackPlayer stopAll";

    for(i=0;i<mediaplayers.size();i++){
        mediaplayers.at(i)->stop();
        delete mediaplayers.at(i);
    }
    mediaplayers.clear();

    this->provisionPlayer();
}
