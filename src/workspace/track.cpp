#include "track.h"

Track::Track(const Track& track):
    QObject(track.parent()),
    path(*track.getPath()),
    loopEnabled(track.isLoopEnabled()),
    startTime(track.getStartTime()),
    endTime(track.getEndTime()),
    fadeInDuration(track.getFadeInDuration()),
    fadeOutDuration(track.getFadeOutDuration())
{
    this->path = *track.getPath();
     QLOG_TRACE() << "Building Track from other track";
}

Track::Track(QObject *parent) :
    QObject(parent)
{
   QLOG_TRACE() << "Building Track from nothing";
}

Track::Track(const QString &url, bool loop, int startTime, int endTime, int fadeInDuration, int fadeOutDuration,QObject *parent) :
    QObject(parent),
    path(url),
    loopEnabled(loop),
    startTime(startTime),
    endTime(endTime),
    fadeInDuration(fadeInDuration),
    fadeOutDuration(fadeOutDuration)
{
    QLOG_TRACE() << "Building Track with full params";
}

Track::Track(const QString &url,QObject *parent) :
    QObject(parent),
    path(url)
{
    QLOG_TRACE() << "Building Track from URL";
}


