#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>
#include <QModelIndex>
#include "playwidgetentrycontroller.h"
#include "workspace.h"

class UiController : public QObject
{
    Q_OBJECT
public:
    explicit UiController(Players * p,Workspace * wsp,QObject *parent = 0);
    PlayWidgetEntryController * getPlayWidgetEntryController();

    void load(Track *);
    long currentPlayerEndingTime();
    
signals:
    void updatePlayerPosition(long position);
    
public slots:
    void pausePlaylist();
    void stopAllButtonClicked();
    void currPlayerPosition(long position);
    void playFromPlaylist(QModelIndex);

private:
    Players * players;
    Workspace * workspace;
    IMediaPlayer * currentPlaylistPlayer;
};

#endif // UICONTROLLER_H
