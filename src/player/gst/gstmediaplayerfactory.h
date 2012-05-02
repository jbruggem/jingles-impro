#ifndef GSTMEDIAPLAYERFACTORY_H
#define GSTMEDIAPLAYERFACTORY_H

#include "mediaplayerfactory.h"
#include "gstplayer.h"

class GstMediaPlayerFactory : public MediaPlayerFactory
{
public:
    GstMediaPlayerFactory();
    IMediaPlayer * getMediaPlayerInstance();
};

#endif // GSTMEDIAPLAYERFACTORY_H
