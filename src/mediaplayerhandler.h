
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
		// We should in fact be using a QMap<QString, QList<MediaPlayerInterface *> > mpMap;
		QMap<QString, QList<LibvlcMediaPlayer> > mpMap;
		// We should also have libvlc_instance_t here to pass to all new LibvlcMediaPlayer instances.
};

#endif