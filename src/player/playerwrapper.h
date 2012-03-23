#ifndef PLAYERWRAPPER_H
#define PLAYERWRAPPER_H

#include <QObject>
#include "QMap"
#include "../common.h"
#include "trackplayer.h"

class PlayerWrapper : public QObject
{
    Q_OBJECT
public:
    explicit PlayerWrapper(MediaPlayerFactory * playerFactory,QObject *parent = 0);
    void load(Track * t);
    void play(Track * t);
    void stopAll(Track * t);

    ~PlayerWrapper(){
    }

private:
    QMap<Track *,TrackPlayer *> players;
    MediaPlayerFactory * playerFactory;

signals:

    
public slots:
    
};

#endif // PLAYERWRAPPER_H
