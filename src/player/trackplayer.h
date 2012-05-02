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
    explicit TrackPlayer(Track * track,IMediaPlayer * player,QObject *parent = 0);
    void play();
    void stop();
    void provisionPlayer();

private:
    Track * track;
    IMediaPlayer * mediaplayer;

signals:
    
public slots:


};

#endif // TRACKPLAYER_H
