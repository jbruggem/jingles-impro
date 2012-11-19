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


    void removePlayer(int pid);
    IMediaPlayer * getPlayer(int playerId);
    IMediaPlayer * getAvailablePlayer(Track * t);
    int createPlayer(Track *t);
    QList<int> * getPlayers(Track * t);
    void stopAll();
    void stopAllForTrack(Track * t);


    ~Players(){
        foreach(IMediaPlayer * player, players.values()){
            delete player;
        }

        foreach(QList<int> * list, playersByTrack.values()){
            delete list;
        }
    }

private:
    QMap<Track *,QList<int> * > playersByTrack;
    QMap<int,IMediaPlayer *> players;
    MediaPlayerFactory * playerFactory;
    double playerIdCounter;
signals:

    
public slots:
    
};

#endif // PLAYERWRAPPER_H
