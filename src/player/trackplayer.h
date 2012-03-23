#ifndef TRACKPLAYER_H
#define TRACKPLAYER_H

#include <QObject>
#include "track.h"
#include "mediaplayerinterface.h"
#include "common.h"
#include "mediaplayerfactory.h"

class TrackPlayer : public QObject
{
    Q_OBJECT
public:
    explicit TrackPlayer(Track * track,MediaPlayerFactory * factory,QObject *parent = 0);
    void playNew();
    void stopAll();
    void provisionPlayer();

private:
    Track * track;
    QList<MediaPlayerInterface *> mediaplayers;
    MediaPlayerFactory * playerFactory;

signals:
    
public slots:


};

#endif // TRACKPLAYER_H
