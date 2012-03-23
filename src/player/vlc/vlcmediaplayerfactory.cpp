#include "vlcmediaplayerfactory.h"

VLCMediaPlayerFactory::VLCMediaPlayerFactory()
{
}



MediaPlayerInterface * VLCMediaPlayerFactory::getMediaPlayerInstance(){
    return new LibvlcMediaPlayer();
}
