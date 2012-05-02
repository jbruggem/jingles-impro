#include "gstmediaplayerfactory.h"



GstMediaPlayerFactory::GstMediaPlayerFactory()
{
}

IMediaPlayer * GstMediaPlayerFactory::getMediaPlayerInstance(){
    return new GstPlayer();
}
