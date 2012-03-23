
#ifndef LIBVLCMEDIAPLAYER_H
#define LIBVLCMEDIAPLAYER_H

#include <vlc/vlc.h>
#include <time.h>
#include "player/mediaplayerinterface.h"
#include "nullptr.h"

class LibvlcMediaPlayer : public MediaPlayerInterface {
	
	public:
		LibvlcMediaPlayer(const char * = nullptr);
		LibvlcMediaPlayer(libvlc_instance_t *, const char * = nullptr);
		LibvlcMediaPlayer(const LibvlcMediaPlayer &);
		~LibvlcMediaPlayer();
		void setFileName(const char *);
		const char * getFileName() const;
		int  play();
		void pause();
		void stop();
		bool isPlaying();
		void print();
		
		static libvlc_instance_t *newLibvlcInstance();
		LibvlcMediaPlayer& operator=(const LibvlcMediaPlayer &);
	private:
		enum StateEnum {
			NOT_INITIALIZED,
			STOPPED,
			PLAYBACK_STARTED,  // means that play() is the last operation that was performed. Does not detect when the end of the track has been reached.
			PAUSED
		} state;
		enum {
			PLAY_START_NB_SECONDS = 2,  // time before we start trusting the output of libvlc_media_player_is_playing() after a call to libvlc_media_player_play()
			MAX_FILE_NAME_LENGTH = 260  // maximum file name length on windows. Including the final '\0' character.
		};
		char fileName[MAX_FILE_NAME_LENGTH];
		// libvlc stuff
		libvlc_instance_t *libvlcInstance;
		libvlc_media_player_t *libvlcMediaPlayer;
		
		time_t timeStartedPlaying;
		
		void init(const char *fileName);
};

#endif
