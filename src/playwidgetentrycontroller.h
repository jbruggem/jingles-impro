#ifndef PLAYWIDGETENTRYCONTROLLER_H
#define PLAYWIDGETENTRYCONTROLLER_H

#include <QObject>
#include "QsLog.h"
#include "track.h"
#include "players.h"

class PlayWidgetEntryController : public QObject
{
    Q_OBJECT
public:
    PlayWidgetEntryController(Players * p, QObject *parent = 0);
    void setTrack(Track * t);

signals:
    void trackInfosUpdated();
    
public slots:
    void playClicked();
    void stopClicked();
    void updateTrackInfos();

private:
    Track * track;
    Players * players;
    //int lastPid;
    void initPlayer();
    
};

#endif // PLAYWIDGETENTRYCONTROLLER_H
