#include "vlcmediaplayerfactory.h"

VLCMediaPlayerFactory::VLCMediaPlayerFactory()
{
}



IMediaPlayer * VLCMediaPlayerFactory::getMediaPlayerInstance(){
    return new LibvlcMediaPlayer();
}
