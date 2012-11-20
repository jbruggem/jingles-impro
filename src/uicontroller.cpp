#include "uicontroller.h"

UiController::UiController(Players * p,Workspace * wsp,QObject *parent) :
    QObject(parent),
    players(p),
    workspace(wsp)
{
}


PlayWidgetEntryController * UiController::getPlayWidgetEntryController(){
    return new PlayWidgetEntryController(players);
}

void UiController::load(Track * t){
    players->createPlayer(t);
}

void UiController::playFromPlaylist(QModelIndex ind){
    QLOG_TRACE() << "[UiController] playFromPlaylist";
    Track * t = workspace->getPlaylist()->at(ind.row());
    if(t)
        players->getAvailablePlayer(t)->play();
}

void UiController::stopAllButtonClicked(){
    QLOG_TRACE() << "[UiController] STOP ALL";
    players->stopAll();
}
