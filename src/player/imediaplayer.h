#ifndef MEDIAPLAYERINTERFACE_H
#define MEDIAPLAYERINTERFACE_H

#include "track.h"

class IMediaPlayer: public QObject{

    public:
        IMediaPlayer(QObject * parent = 0): QObject(parent){}
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
        virtual long getEndingTime() = 0;
        //virtual void print() = 0;
    signals:
         virtual void stateChanged() = 0;
         virtual void updatePosition(long updatePosition) = 0; // in millisec

	private:
		// MediaPlayerInterface& operator=(const MediaPlayerInterface&);
		// MediaPlayerInterface(const MediaPlayerInterface&);
		// MediaPlayerInterface() {}
};

#endif
