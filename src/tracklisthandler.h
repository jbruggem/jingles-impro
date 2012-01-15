
#ifndef TRACKLISTHANDLER_H
#define TRACKLISTHANDLER_H

#include <stdint.h>
#include <QStringList>
#include "avobject.h"

class TrackListHandler {
	public:
		TrackListHandler();
		void add(QString &);
		void add(QStringList &);
		void remove(int32_t);
		void remove(QList<int32_t> &);
		void setPath(int32_t, QString &);
		QString getPath(int32_t) const;
		bool hasPath(int32_t);
		bool exists(int32_t);
		void play(int32_t);
		void stop(int32_t);
		bool isPlaying(int32_t);
		void clear();
		void print() const;
	
	private:
		QList<AVObject> trackList;
};


#endif
