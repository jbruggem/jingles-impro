#include "track.h"
#include "nullptr.h"

//xxx do we want the copy constructor to use a new fileRef or just copy the other object's pointer?
Track::Track(const Track& track):
    QObject(track.parent()),
    path(track.path),
    loopEnabled(track.loopEnabled),
    startTime(track.startTime),
    endTime(track.endTime),
    fadeInDuration(track.fadeInDuration),
    fadeOutDuration(track.fadeOutDuration),
    fileRef(track.fileRef)
{
     QLOG_TRACE() << "Building Track from other track";
}

Track::Track(QObject *parent) :
    QObject(parent),
    path(),
    loopEnabled(false),
    startTime(0),
    endTime(0),
    fadeInDuration(0),
    fadeOutDuration(0),
    fileRef(nullptr)
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

    // conversion of QString to const char * according to
    // http://qt-project.org/faq/answer/how_can_i_convert_a_qstring_to_char_and_vice_versa
    QByteArray temp = url.toLocal8Bit();
    fileRef = new TagLib::FileRef(temp.data());
}

Track::Track(const QString &url,QObject *parent) :
    QObject(parent),
    path(url),
    loopEnabled(false),
    startTime(0),
    endTime(0),
    fadeInDuration(0),
    fadeOutDuration(0)
{
    QLOG_TRACE() << "Building Track from URL";

    // conversion of QString to const char * according to
    // http://qt-project.org/faq/answer/how_can_i_convert_a_qstring_to_char_and_vice_versa
    QByteArray temp = url.toLocal8Bit();
    fileRef = new TagLib::FileRef(temp.data());
}


