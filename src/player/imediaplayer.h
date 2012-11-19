#ifndef MEDIAPLAYERINTERFACE_H
#define MEDIAPLAYERINTERFACE_H

#include "track.h"

class IMediaPlayer{

    public:
		virtual ~IMediaPlayer() {}
        virtual Track * getTrack() = 0;
        virtual void setTrack(Track *) = 0;
        virtual void load() = 0;
        //virtual void setUri(const char *) = 0;
        //virtual const char * getUri() const = 0;
		virtual int  play() = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;
		virtual bool isPlaying() = 0;
        virtual bool isLoaded() = 0;
        virtual bool hasError() = 0;
        //virtual void print() = 0;
	private:
		// MediaPlayerInterface& operator=(const MediaPlayerInterface&);
		// MediaPlayerInterface(const MediaPlayerInterface&);
		// MediaPlayerInterface() {}
};

#endif
