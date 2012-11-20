
#ifndef TRACKLIST_H_
#define TRACKLIST_H_

#include <QList>
#include <iostream>
#include "track.h"
#include <QAbstractListModel>

class TrackList : public  QAbstractListModel, public QList<Track *> {

	Q_OBJECT

	public:
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        int rowCount(const QModelIndex &parent = QModelIndex()) const;

        TrackList(QObject *parent = 0);
		friend std::ostream& operator<< (std::ostream &out, const TrackList &list);
};

#endif
