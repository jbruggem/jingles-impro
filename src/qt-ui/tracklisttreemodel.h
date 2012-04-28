
#ifndef TRACKLISTTREEMODEL_H_
#define TRACKLISTTREEMODEL_H_

#include <QStandardItemModel>
#include <QStringList>

class TrackList;

class TrackListTreeModel : public QStandardItemModel {

	Q_OBJECT

	public:
		enum SortingMode {
			SortByArtist,
			SortByFolder,
			NbSortingModes,
		};
		TrackListTreeModel(QObject *parent = 0);
		void addTrack(const QString &path, bool refreshAfterAdd = true);
		void addTracks(const QStringList &);
		void populate(const TrackList *);
		static QString getSortingModeText(SortingMode);
		void setSortingMode(SortingMode);
	public slots:
		void setSortingMode(int);
	private:
		void refresh();
		TrackList *trackList;
		SortingMode sortingMode;
		static QStringList sortingModeTexts;
};

#endif
