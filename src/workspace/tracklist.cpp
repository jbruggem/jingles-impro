
#include "tracklist.h"

TrackList::TrackList(QObject *parent) : QObject(parent) {
}

std::ostream& operator<< (std::ostream &out, const TrackList &list) {
	for (int i = 0; i < list.size(); i++){
		const Track *t = list.at(i);
		out << "\n   Track[" << t->getPath().toStdString() << "|"
							 << t->getStartTime()
							 << "-"
							 << t->getEndTime()
							 << "]";
	}
	return out;
}
