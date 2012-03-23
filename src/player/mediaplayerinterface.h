
#ifndef MEDIAPLAYERINTERFACE_H
#define MEDIAPLAYERINTERFACE_H

class MediaPlayerInterface {
	public:
		virtual ~MediaPlayerInterface() {}
		virtual void setFileName(const char *) = 0;
		virtual const char * getFileName() const = 0;
		virtual int  play() = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;
		virtual bool isPlaying() = 0;
		virtual void print() = 0;
	private:
		// MediaPlayerInterface& operator=(const MediaPlayerInterface&);
		// MediaPlayerInterface(const MediaPlayerInterface&);
		// MediaPlayerInterface() {}
};

#endif
