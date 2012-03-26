
#ifndef TRACKSTOCK_H
#define TRACKSTOCK_H

#include "tracklist.h"

class TrackStock : public TrackList {

	Q_OBJECT

	public:
		TrackStock(QObject *parent = 0);
};

#endif
