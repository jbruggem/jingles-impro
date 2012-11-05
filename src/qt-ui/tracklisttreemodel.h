
#ifndef TRACKLISTTREEMODEL_H_
#define TRACKLISTTREEMODEL_H_

#include <QStandardItemModel>
#include <QMap>

#include "tracklist.h"

class TrackListTreeModel : public QStandardItemModel {

	Q_OBJECT

	public:
		enum SortingMode {
			SortByArtist,
			SortByFolder,
			NbSortingModes,
		};
		TrackListTreeModel(QObject *parent = 0);
		void addTrack(const QString &);
		void addTracks(const QStringList &);
		void populate(const TrackList *);
		static QString getSortingModeText(SortingMode);
		void setSortingMode(SortingMode);
		Track *getTrack(const QModelIndex &) const;
	public slots:
		void setSortingMode(int);
		void printItem(const QModelIndex &) const;
	private:
		void addTrack(const QString &path, bool refreshAfterAdd = true);
		void refresh();
		TrackList *trackList;
		TrackList  sortedTrackList;
		SortingMode sortingMode;
		static QMap<SortingMode, QString> sortingModeTexts;
		static QMap<SortingMode, QString> getSortingModeTexts();
};

#endif
