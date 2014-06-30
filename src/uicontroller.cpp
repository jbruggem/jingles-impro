#include "uicontroller.h"

UiController::UiController(Players * p,Workspace * wsp,QObject *parent) :
    QObject(parent),
    players(p),
    workspace(wsp),
    currentPlaylistPlayer(NULL)
{
}


PlayWidgetEntryController * UiController::getPlayWidgetEntryController(){
    return new PlayWidgetEntryController(players);
}

void UiController::load(Track * t){
    players->getAvailablePlayer(t);
}

long  UiController::currentPlayerEndingTime(){
    if(currentPlaylistPlayer){
        return currentPlaylistPlayer->getEndingTime();
    }
    return -1;
}

void UiController::pausePlaylist(){
    if(currentPlaylistPlayer){
        if(currentPlaylistPlayer->isPlaying()){
            currentPlaylistPlayer->pause();
        }else
            currentPlaylistPlayer->play();
    }
}

void UiController::playFromPlaylist(QModelIndex ind){
    QLOG_TRACE() << "[UiController] playFromPlaylist";

    if(currentPlaylistPlayer){
        disconnect(currentPlaylistPlayer,SIGNAL(updatePosition(long)),this,SLOT(currPlayerPosition(long)));
        currentPlaylistPlayer->stop();
    }

    Track * t = workspace->getPlaylist()->at(ind.row());
    if(t){
        currentPlaylistPlayer = players->getAvailablePlayer(t);

        if(currentPlaylistPlayer){
            connect(currentPlaylistPlayer,SIGNAL(updatePosition(long)),this,SLOT(currPlayerPosition(long)));
            currentPlaylistPlayer->play();
        }
    }
}

void UiController::currPlayerPosition(long position){
    this->updatePlayerPosition(position);
}

void UiController::stopAllButtonClicked(){
    QLOG_TRACE() << "[UiController] STOP ALL";
    players->stopAll();
}
