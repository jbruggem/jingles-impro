#include "playwidgetentrycontroller.h"

PlayWidgetEntryController::PlayWidgetEntryController(Players * p, QObject *parent)
    : QObject (parent),
      track(NULL),
      players(p),
      lastPid(-1){


}

void PlayWidgetEntryController::setTrack(Track * t){
    track = t;
    connect(t,SIGNAL(tagUpdated()),this,SLOT(updateTrackInfos()));
    initPlayer();
}

void PlayWidgetEntryController::initPlayer(){
    lastPid = players->createPlayer(track);
}

void PlayWidgetEntryController::playClicked(){
    QLOG_TRACE() << "Button play was clicked";
    if(NULL != track){
        IMediaPlayer * player = players->getPlayer(lastPid);
        if(NULL != player){
            player->play();
        }else{
            QLOG_ERROR() << "We should have a player ready to play: none was found. Can't play.";
        }
        initPlayer();
    }
}


void PlayWidgetEntryController::updateTrackInfos(){
    QLOG_TRACE() << "PlayWidgetEntryController::updateTrackInfos";
    emit trackInfosUpdated();
}

void PlayWidgetEntryController::stopClicked(){
    QLOG_TRACE() << "Button stop was clicked";
    if(NULL != track){
        players->stopAllForTrack(track);
    }
    initPlayer();
}
