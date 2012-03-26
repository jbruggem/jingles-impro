
#ifndef TRACKPLAYLIST_H
#define TRACKPLAYLIST_H

#include "tracklist.h"

class TrackPlaylist : public TrackList {

	Q_OBJECT

	public:
		TrackPlaylist(QObject *parent = 0);
};

#endif
