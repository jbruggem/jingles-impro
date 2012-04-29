
#include "libvlcmediaplayer.h"

#include "QsLog.h"

LibvlcMediaPlayer::LibvlcMediaPlayer(const char *fileName) {
	QLOG_TRACE() << "LibvlcMediaPlayer::LibvlcMediaPlayer(const char *fileName) |" << (fileName? fileName : "no file");
	
	// Create new VLC engine 
	libvlcInstance = libvlc_new (0, nullptr);
	
	init(fileName);
}

LibvlcMediaPlayer::LibvlcMediaPlayer(libvlc_instance_t *inst, const char *fileName) {
	QLOG_TRACE() << "LibvlcMediaPlayer::LibvlcMediaPlayer(libvlc_instance_t *inst, const char *fileName) |" << (fileName? fileName : "no file");

	// Try/catch needed here
	if (inst) {
		// Attach to the existing VLC engine 
		libvlcInstance = inst;
	} else {
		// Create new VLC engine 
		libvlcInstance = libvlc_new (0, nullptr);
	}
	
	init(fileName);
}

LibvlcMediaPlayer::LibvlcMediaPlayer(const LibvlcMediaPlayer &other) {
	QLOG_TRACE() << "LibvlcMediaPlayer::LibvlcMediaPlayer(const LibvlcMediaPlayer &other) |" << (other.fileName? other.fileName : "no file");

	// Try/catch needed here
	if (other.libvlcInstance) {
		// Attach to the existing VLC engine 
		libvlcInstance = other.libvlcInstance;
	} else {
		// Create new VLC engine 
		libvlcInstance = libvlc_new (0, nullptr);
	}
	
	init(other.fileName);
}

LibvlcMediaPlayer& LibvlcMediaPlayer::operator=(const LibvlcMediaPlayer &other) {
	QLOG_TRACE() << "LibvlcMediaPlayer::operator=() |" << (other.fileName? other.fileName : "no file");

	// protect against invalid self-assignment
	if (this == &other) {
		return *this;
	}
	
	// Free the media_player and the libvlc instance 
	stop();
	libvlc_media_player_release (libvlcMediaPlayer);
	libvlc_release (libvlcInstance);
	
	// Try/catch needed here
	if (other.libvlcInstance) {
		// Attach to the existing VLC engine 
		libvlcInstance = other.libvlcInstance;
	} else {
		// Create new VLC engine 
		libvlcInstance = libvlc_new (0, nullptr);
	}
	
	init(other.fileName);
	return *this;
}

LibvlcMediaPlayer::~LibvlcMediaPlayer() {
	QLOG_TRACE() << "LibvlcMediaPlayer::~LibvlcMediaPlayer() |" << (fileName? fileName : "no file");
	// Free the media_player and the libvlc instance 
	stop();
	libvlc_media_player_release (libvlcMediaPlayer);
	libvlc_release (libvlcInstance);
}

void LibvlcMediaPlayer::init(const char *fileName) {
	QLOG_TRACE() << "LibvlcMediaPlayer::init() |" << (fileName? fileName : "no file");
	// Initialise timeStartedPlaying just so it doesn't have an undefined value
	timeStartedPlaying = 0;
	
	state = NOT_INITIALIZED;
	
	// Create a media player playing environement 
	libvlcMediaPlayer = libvlc_media_player_new (libvlcInstance);
	
	// Try/catch needed here
	if (not fileName) {
		memset(const_cast<char *>(this->fileName), 0, sizeof(this->fileName));
		return;
	}
	strncpy(this->fileName, fileName, MAX_FILE_NAME_LENGTH - 1);
	this->fileName[MAX_FILE_NAME_LENGTH - 1] = '\0';

	// Create a new item 
	libvlc_media_t *m = libvlc_media_new_path (libvlcInstance, this->fileName);

	// Link the media to the media player 
	libvlc_media_player_set_media (libvlcMediaPlayer, m);

	// No need to keep the media now 
	libvlc_media_release (m);
	
	state = STOPPED;
}

void LibvlcMediaPlayer::setFileName(const char *fileName) {
	QLOG_TRACE() << "setFileName()";
	if (not fileName) {
		return;
	}
	strncpy(this->fileName, fileName, MAX_FILE_NAME_LENGTH - 1);
	this->fileName[MAX_FILE_NAME_LENGTH - 1] = '\0';
	
	// Create a new item 
	libvlc_media_t *m = libvlc_media_new_path (libvlcInstance, this->fileName);

	// Modify the media player playing environement 
	libvlc_media_player_set_media (libvlcMediaPlayer, m);

	// No need to keep the media now 
	libvlc_media_release (m);
}

const char * LibvlcMediaPlayer::getFileName() const {
	return fileName;
}

int LibvlcMediaPlayer::play() {
	QLOG_TRACE() << "LibvlcMediaPlayer::play() |" << (fileName? fileName : "no file");
    // Play/resume the media_player
    QLOG_TRACE() << "state" << libvlc_media_player_get_state(libvlcMediaPlayer);

    /*
    libvlc_media_player_play (libvlcMediaPlayer);
    libvlc_media_player_pause (libvlcMediaPlayer);
    libvlc_media_player_set_time(libvlcMediaPlayer,5000);
    //*/
    int error = libvlc_media_player_play (libvlcMediaPlayer);

	if (not error) {
		// Playback was successfully started, so we store the initial time
		timeStartedPlaying = time(nullptr);
		state = PLAYBACK_STARTED;
	}

/*
    int fadeDuration = 10000; // milliseconds
    int startVolume = 0; //libvlc_audio_get_volume(libvlcMediaPlayer);
    int endVolume = 120;
    int factor = 1;
    int microStep = factor*fadeDuration*1000/(endVolume-startVolume);

    QLOG_TRACE() << "step" << microStep;

    for(int i=startVolume; i <= endVolume; i+=factor){
        libvlc_audio_set_volume(libvlcMediaPlayer,i);
        usleep(microStep);
    }
    libvlc_audio_set_volume(libvlcMediaPlayer,endVolume);


    QLOG_TRACE() << "volue " << libvlc_audio_get_volume (libvlcMediaPlayer);*/
    //for(int i)

	return error;
}

void LibvlcMediaPlayer::pause() {
	QLOG_TRACE() << "LibvlcMediaPlayer::pause() |" << (fileName? fileName : "no file");
	if (state == PLAYBACK_STARTED) {
		// Pause the media_player 
		libvlc_media_player_set_pause (libvlcMediaPlayer, true);
		state = PAUSED;
	}
}

void LibvlcMediaPlayer::stop() {
	QLOG_TRACE() << "LibvlcMediaPlayer::stop() |" << (fileName? fileName : "no file");
	// Stop the media_player 
	libvlc_media_player_stop (libvlcMediaPlayer);
	state = STOPPED;
}

bool LibvlcMediaPlayer::isPlaying() {
	if (state != PLAYBACK_STARTED) {
		return false;
	}
	time_t currentTime = time(nullptr);
	if (currentTime > timeStartedPlaying + PLAY_START_NB_SECONDS) {
		if (libvlc_media_player_is_playing (libvlcMediaPlayer)) {
			// The track is still playing
			return true;
		} else {
			// The end of the track has been reached
			state = STOPPED;
			return false;
		}
	} else {
		// Not enough time has passed since the call to libvlc_media_player_play(). We don't trust the output of libvlc_media_player_is_playing() yet.
		return true;
	}
}

void LibvlcMediaPlayer::print() {
	// Get rid of the \n at the end of the string returned by ctime()
	char *timeString = ctime(&timeStartedPlaying);
	timeString[24] = '\0';
	
	QLOG_INFO() << "LibvlcMediaPlayer |" 
		<< (fileName? fileName : "no file") << "|" 
		<< (isPlaying()? "playing" : "stopped") << "|" 
		<< "time started playing:" << timeString;
}

libvlc_instance_t *LibvlcMediaPlayer::newLibvlcInstance() {
	// Create new VLC engine 
	return libvlc_new (0, nullptr);
}
