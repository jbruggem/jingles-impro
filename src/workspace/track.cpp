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
    std::cout << "Building Track from other track"<<std::endl;
}

Track::Track(QObject *parent) :
    QObject(parent)
{
    std::cout << "Building Track from nothing"<<std::endl;
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
    std::cout << "Building Track with full params"<<std::endl;
}

Track::Track(const QString &url,QObject *parent) :
    QObject(parent),
    path(url)
{
    std::cout << "Building Track from URL"<<std::endl;
}


