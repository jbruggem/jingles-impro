
#ifndef TRACKLISTTABLEMODEL_H_
#define TRACKLISTTABLEMODEL_H_

#include <QStandardItemModel>
#include <QMap>

#include "tracklist.h"

class TrackListTableModel : public QStandardItemModel {

    Q_OBJECT

    public:
        TrackListTableModel(QObject *parent = 0);
        void addTrack(const QString &);
        void addTracks(const QStringList &);
        void populate(const TrackList *);
    private:
        void initHeader();
        void addTrack(const QString &path, bool refreshAfterAdd = true);
        void refresh();
        TrackList *trackList;
};

#endif
