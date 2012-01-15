
#ifndef AVOBJECT_H
#define AVOBJECT_H

#include <vlc/vlc.h>

class AVObject {
	
	public:
		AVObject();
		AVObject(const char *);
		AVObject(const AVObject &);
		~AVObject();
		void setPath(const char *);
		const char * getPath() const;
	
	public:
		void play();
		void stop();
		bool isPlaying();
	
	private:
		enum StateEnum {
			NOT_INITIALIZED,
			STOPPED,
			PLAYING
		} state;
		enum {
			MAX_PATH_LENGTH = 260  // on windows. Including the final '\0' character.
		};
		char path[MAX_PATH_LENGTH];
		// libvlc stuff
		libvlc_instance_t *inst;
		libvlc_media_player_t *mp;
		libvlc_media_t *m;
		
		void init(const char *path);
};

#endif
