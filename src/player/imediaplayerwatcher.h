#ifndef IMEDIAPLAYERWATCHER_H
#define IMEDIAPLAYERWATCHER_H

#include <QThread>
#include "imediaplayer.h"

class IMediaPlayerWatcher : public QThread
{
    Q_OBJECT
public:
    IMediaPlayerWatcher(IMediaPlayer * player, int duration,  QObject * parent = 0);

protected:
    void run();

private:
    IMediaPlayer * player;
    int duration; // miliseconds

signals:
    
public slots:
    
};

#endif // IMEDIAPLAYERWATCHER_H
