
#ifndef MEDIAPLAYERHANDLER_H
#define MEDIAPLAYERHANDLER_H

#include <QMap>
#include "libvlcmediaplayer.h"

class MediaPlayerHandler {
	public:
		MediaPlayerHandler();
		void play(const QString &);
		void stop(const QString &);
		void stop();
		void print();
	private:
		void cleanup();
		QMap<QString, QList<MediaPlayerInterface *> > mpMap;
};

#endif