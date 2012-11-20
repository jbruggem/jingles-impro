#include "uicontroller.h"

UiController::UiController(Players * p,QObject *parent) :
    QObject(parent),
    players(p)
{
}


PlayWidgetEntryController * UiController::getPlayWidgetEntryController(){
    return new PlayWidgetEntryController(players);
}


void UiController::stopAllButtonClicked(){
    QLOG_TRACE() << "[UiController] STOP ALL";
    players->stopAll();
}
