#include "playwidgetentrycontroller.h"

PlayWidgetEntryController::PlayWidgetEntryController(Players * p, QObject *parent)
    : QObject (parent),
      track(NULL),
      players(p)
    //,lastPid(-1)
{
    connect(p,SIGNAL(playingStateChange(Track*,bool)),this,SLOT(playingStateChange(Track*,bool)));
}

void PlayWidgetEntryController::playingStateChange(Track *t, bool isNowPlaying){
    if(t == track){
        this->stateChanged(isNowPlaying);
    }
}

void PlayWidgetEntryController::setTrack(Track * t){
    track = t;
    connect(t,SIGNAL(tagUpdated()),this,SLOT(updateTrackInfos()));
    initPlayer();
}

void PlayWidgetEntryController::initPlayer(){
    players->getAvailablePlayer(track);
}

void PlayWidgetEntryController::playClicked(){
    //QLOG_TRACE() << "Button play was clicked";
    if(NULL != track){
        IMediaPlayer * player = players->getAvailablePlayer(track);
        if(NULL != player){
            player->play();
        }else{
            QLOG_ERROR() << "No player to play.";
        }
    }
}


void PlayWidgetEntryController::updateTrackInfos(){
    //QLOG_TRACE() << "PlayWidgetEntryController::updateTrackInfos";
    emit trackInfosUpdated();
}

void PlayWidgetEntryController::stopClicked(){
    QLOG_TRACE() << "Button stop was clicked";
    if(NULL != track){
        players->stopAllForTrack(track);
        //this->stateChanged(false);
    }
    initPlayer();
}
