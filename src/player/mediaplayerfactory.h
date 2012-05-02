#ifndef MEDIAPLAYERFACTORY_H
#define MEDIAPLAYERFACTORY_H

#include "imediaplayer.h"

class MediaPlayerFactory //: public QObject
{
    //Q_OBJECT
    public:
        //MediaPlayerFactory(); //QObject *parent = 0):QObject(parent){}
        virtual ~MediaPlayerFactory() {}
        virtual IMediaPlayer * getMediaPlayerInstance() = 0;
};

#endif // MEDIAPLAYERFACTORY_H
