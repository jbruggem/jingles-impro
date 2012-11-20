#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>
#include "playwidgetentrycontroller.h"

class UiController : public QObject
{
    Q_OBJECT
public:
    explicit UiController(Players * p,QObject *parent = 0);
    PlayWidgetEntryController * getPlayWidgetEntryController();
    
signals:
    
public slots:
    void stopAllButtonClicked();

private:
    Players * players;
};

#endif // UICONTROLLER_H
