
#include "avobject.h"

#include <cstring>
#include "nullptr.h"

AVObject::AVObject() :
	inst (nullptr),
	mp   (nullptr),
	m    (nullptr) {
	
	memset(path, 0, sizeof(path));
}

AVObject::~AVObject() {
	/* Free the media_player */
	libvlc_media_player_release (mp);
	libvlc_release (inst);
}

AVObject::AVObject(const char *path) {
	init(path);
}

AVObject::AVObject(const AVObject &other) {
	init(other.path);
}

void AVObject::init(const char *path) {
	
	if (path) {
		strncpy(this->path, path, MAX_PATH_LENGTH - 1);
		this->path[MAX_PATH_LENGTH - 1] = '\0';
	} else {
		memset(const_cast<char *>(path), 0, sizeof(path));
	}
	
	/* Load the VLC engine */
	inst = libvlc_new (0, NULL);

	/* Create a new item */
	m = libvlc_media_new_path (inst, this->path);

	/* Create a media player playing environement */
	mp = libvlc_media_player_new_from_media (m);

	/* No need to keep the media now */
	libvlc_media_release (m);
}

void AVObject::setPath(const char *path) {
	if (path) {
		strncpy(this->path, path, MAX_PATH_LENGTH - 1);
		this->path[MAX_PATH_LENGTH - 1] = '\0';
		
		/* Create a new item */
		m = libvlc_media_new_path (inst, this->path);

		/* Modify the media player playing environement */
		libvlc_media_player_set_media (mp, m);

		/* No need to keep the media now */
		libvlc_media_release (m);
	}
}

const char * AVObject::getPath() const {
	return path;
}

void AVObject::play() {
	/* play the media_player */
	libvlc_media_player_play (mp);
}

void AVObject::stop() {
	/* Stop playing */
	libvlc_media_player_stop (mp);
}

bool AVObject::isPlaying() {
	return libvlc_media_player_is_playing (mp);
}
