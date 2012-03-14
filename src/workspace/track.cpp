#include "track.h"

Track::Track(const Track& track){
    this->setParent(track.parent());
}

Track::Track(QObject *parent) :
    QObject(parent)
{
}

Track::Track(const QString &url, bool loop, int startTime, int endTime, int fadeInDuration, int fadeOutDuration,QObject *parent) :
    QObject(parent)
{
}

Track::Track(const QString &url,QObject *parent) :
    QObject(parent)
{
}


