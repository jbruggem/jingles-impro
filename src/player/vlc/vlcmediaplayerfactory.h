#ifndef VLCMEDIAPLAYERFACTORY_H
#define VLCMEDIAPLAYERFACTORY_H

#include "mediaplayerfactory.h"
#include "libvlcmediaplayer.h"

class VLCMediaPlayerFactory : public MediaPlayerFactory
{
public:
    VLCMediaPlayerFactory();
    IMediaPlayer * getMediaPlayerInstance();

};

#endif // VLCMEDIAPLAYERFACTORY_H
