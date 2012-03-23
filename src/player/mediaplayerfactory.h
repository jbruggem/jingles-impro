#ifndef MEDIAPLAYERFACTORY_H
#define MEDIAPLAYERFACTORY_H

#include "mediaplayerinterface.h"

class MediaPlayerFactory
{
    public:
        virtual ~MediaPlayerFactory() {}
        virtual MediaPlayerInterface * getMediaPlayerInstance() = 0;
};

#endif // MEDIAPLAYERFACTORY_H
