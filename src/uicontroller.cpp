#include "uicontroller.h"

UiController::UiController(Players * p,QObject *parent) :
    QObject(parent),
    players(p)
{
}


PlayWidgetEntryController * UiController::getPlayWidgetEntryController(){
    return new PlayWidgetEntryController(players);
}
