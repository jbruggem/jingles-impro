
#include "mediaplayerhandler.h"

#include <QString>
#include "QsLog.h"

MediaPlayerHandler::MediaPlayerHandler() {
	
}

void MediaPlayerHandler::play(const QString &fileName) {
	mpMap[fileName].append(fileName.toLocal8Bit().constData());
	mpMap[fileName].last().play();
	cleanup();
}

void MediaPlayerHandler::stop(const QString &fileName) {
	mpMap.remove(fileName);
}

void MediaPlayerHandler::stop() {
	mpMap.clear();
}

void MediaPlayerHandler::cleanup() {
	QMutableMapIterator<QString, QList<LibvlcMediaPlayer> > i(mpMap);
	
	while (i.hasNext()) {
		i.next();
		for (int j = 0; j < i.value().length(); j++) {
			if (not i.value()[j].isPlaying()) {
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
	
	QMutableMapIterator<QString, QList<LibvlcMediaPlayer> > i(mpMap);
	
	while (i.hasNext()) {
		i.next();
		int instancesPlaying = 0;
		for (int j = 0; j < i.value().length(); j++) {
			if (i.value()[j].isPlaying()) {
				instancesPlaying++;
			}
		}
		QLOG_INFO() << "--" << i.key() << "|" << i.value().length() << "instances" << "|" << instancesPlaying << "playing";
	}
	QLOG_INFO() << "--" << "end";
}
