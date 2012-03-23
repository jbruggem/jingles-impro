#ifndef VLCMEDIAPLAYERFACTORY_H
#define VLCMEDIAPLAYERFACTORY_H

#include "mediaplayerfactory.h"
#include "libvlcmediaplayer.h"

class VLCMediaPlayerFactory : public MediaPlayerFactory
{
public:
    VLCMediaPlayerFactory();
    MediaPlayerInterface * getMediaPlayerInstance();

};

#endif // VLCMEDIAPLAYERFACTORY_H
