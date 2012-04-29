#include "trackplayer.h"

TrackPlayer::TrackPlayer(Track * track,MediaPlayerInterface * player,QObject *parent) :
    QObject(parent),
    track(track),
    mediaplayer(player)
{
    this->provisionPlayer();
}

void TrackPlayer::provisionPlayer(){
    QLOG_TRACE() << "Provisionning media player";

    mediaplayer->setFileName(this->track->getPath()->toStdString().c_str());


}

void TrackPlayer::play(){
    QLOG_TRACE() << "TrackPlayer playNew";
    mediaplayer->play();
}

void TrackPlayer::stop(){
    QLOG_TRACE() << "TrackPlayer stop";

    mediaplayer->stop();
}
