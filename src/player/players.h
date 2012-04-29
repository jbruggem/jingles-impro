#ifndef PLAYERWRAPPER_H
#define PLAYERWRAPPER_H

#include <QObject>
#include "QMap"
#include "common.h"
#include "trackplayer.h"

class Players : public QObject
{
    Q_OBJECT
public:
    explicit Players(MediaPlayerFactory * playerFactory,QObject *parent = 0);
    int load(Track * t);
    int play(int trackId);
    void stop(int trackId);
    void stopAll(Track * t);

    ~Players(){
    }

private:
    QMap<Track *,int> playersByTrack;
    QMap<int,TrackPlayer *> players;
    MediaPlayerFactory * playerFactory;

signals:

    
public slots:
    
};

#endif // PLAYERWRAPPER_H
