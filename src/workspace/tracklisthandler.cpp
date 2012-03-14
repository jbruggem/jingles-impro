
#include "tracklisthandler.h"

#include "QsLog.h"

TrackListHandler::TrackListHandler() {
}

void TrackListHandler::add(QString &path) {
	trackList.append(path.toLocal8Bit().constData());
}

void TrackListHandler::add(QStringList &paths) {
	foreach(const QString &p, paths) {
		trackList.append(p.toLocal8Bit().constData());
	}
}

void TrackListHandler::remove(int32_t index) {
	trackList.removeAt(index);
}

void TrackListHandler::remove(QList<int32_t> &indexes) {
	foreach(int32_t i, indexes) {
		trackList.removeAt(i);
	}
}

void TrackListHandler::setPath(int32_t index, QString &path) {
	trackList[index].setPath(path.toLocal8Bit().constData());
}

QString TrackListHandler::getPath(int32_t index) const {
	return QString(trackList.at(index).getPath());
}

bool TrackListHandler::hasPath(int32_t index) {
	return not QString(trackList[index].getPath()).isEmpty();
}

bool TrackListHandler::exists(int32_t index) {
	return trackList.length() > index;
}

void TrackListHandler::play(int32_t index) {
	trackList[index].play();
}

void TrackListHandler::stop(int32_t index) {
	trackList[index].stop();
}

bool TrackListHandler::isPlaying(int32_t index) {
	return trackList[index].isPlaying();
}

void TrackListHandler::clear() {
	trackList.clear();
}

void TrackListHandler::print() const {
	for (int32_t i = 0; i < trackList.length(); i++) {
		QLOG_INFO() << '\t' << i << " | " << trackList.at(i).getPath();
	}
}
