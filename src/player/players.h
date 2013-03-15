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

    static const int MAX_NUM_PLAYERS = 10;

    void removePlayer(int pid);
    IMediaPlayer * getPlayer(int playerId);
    IMediaPlayer * getAvailablePlayer(Track * t);
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
    signals:
        void playingStateChange(Track *,bool playing);

private:
    int createPlayer(Track *t);
    QMap<Track *,QList<int> * > playersByTrack;
    QMap<int,IMediaPlayer *> players;
    MediaPlayerFactory * playerFactory;
    double playerIdCounter;
    void ensureTrackExists(Track *t);
signals:

    
public slots:
    void playerStateChanged();
};

#endif // PLAYERWRAPPER_H
