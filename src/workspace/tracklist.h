
#ifndef TRACKLIST_H_
#define TRACKLIST_H_

#include <QList>
#include <iostream>
#include "track.h"
#include <QAbstractListModel>

class TrackList : public  QObject, public QList<Track *> {

	Q_OBJECT

    public:

        TrackList(QObject *parent = 0);
		friend std::ostream& operator<< (std::ostream &out, const TrackList &list);
};

#endif
