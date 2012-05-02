#ifndef PLAYERWRAPPER_H
#define PLAYERWRAPPER_H

#include <QObject>
#include "QMap"
#include "QList"
#include "common.h"
#include "imediaplayer.h"
#include "mediaplayerfactory.h"
#include "track.h"

class Players : public QObject
{
    Q_OBJECT
public:
    explicit Players(MediaPlayerFactory * playerFactory,QObject *parent = 0);


    double createPlayer(Track * t);
    IMediaPlayer * getPlayer(double playerId);
    QList<double> * getPlayers(Track * t);
    void stopAll();
    void stopAllForTrack(Track * t);


    ~Players(){
        foreach(IMediaPlayer * player, players.values()){
            delete player;
        }

        foreach(QList<double> * list, playersByTrack.values()){
            delete list;
        }
    }

private:
    QMap<Track *,QList<double> * > playersByTrack;
    QMap<double,IMediaPlayer *> players;
    MediaPlayerFactory * playerFactory;
    double playerIdCounter;
signals:

    
public slots:
    
};

#endif // PLAYERWRAPPER_H
