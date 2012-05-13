#include "imediaplayerwatcher.h"

IMediaPlayerWatcher::IMediaPlayerWatcher(IMediaPlayer * player,int duration,QObject *parent) :
    QThread(parent),
    player(player),
    duration(duration)
{
}

void IMediaPlayerWatcher::run(){
    this->msleep(duration);
    player->stop();
}
