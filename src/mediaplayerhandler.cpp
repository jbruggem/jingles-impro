
#include "mediaplayerhandler.h"

#include <QString>
#include "QsLog.h"

MediaPlayerHandler::MediaPlayerHandler() {
	
}

void MediaPlayerHandler::play(const QString &fileName) {
	// TODO: use the factory design pattern here to generate the LibvlcMediaPlayer instance
	mpMap[fileName].append(new LibvlcMediaPlayer(fileName.toLocal8Bit().constData()));
	mpMap[fileName].last()->play();
	cleanup();
}

void MediaPlayerHandler::stop(const QString &fileName) {
	if (mpMap.contains(fileName)) {
		qDeleteAll(mpMap[fileName]);
		mpMap.remove(fileName);
	}
}

void MediaPlayerHandler::stop() {
	foreach (const QList<MediaPlayerInterface *> &l, mpMap) {
		qDeleteAll(l);
	}
	mpMap.clear();
}

void MediaPlayerHandler::cleanup() {
	QLOG_INFO() << "MediaPlayerHandler::cleanup()";
	QMutableMapIterator<QString, QList<MediaPlayerInterface *> > i(mpMap);
	
	while (i.hasNext()) {
		i.next();
		for (int j = 0; j < i.value().length(); j++) {
			if (not i.value()[j]->isPlaying()) {
				delete i.value()[j];
				i.value().removeAt(j);
				j--;
			}
		}
		if (i.value().isEmpty()) {
			mpMap.remove(i.key());
		}
	}
}

void MediaPlayerHandler::print() {
	QLOG_INFO() << "MediaPlayerHandler::print()";
	
	QMutableMapIterator<QString, QList<MediaPlayerInterface *> > i(mpMap);
	
	while (i.hasNext()) {
		i.next();
		int instancesPlaying = 0;
		for (int j = 0; j < i.value().length(); j++) {
			if (i.value()[j]->isPlaying()) {
				instancesPlaying++;
			}
		}
		QLOG_INFO() << "--" << i.key() << "|" << i.value().length() << "instances" << "|" << instancesPlaying << "playing";
	}
	QLOG_INFO() << "--" << "end";
}
