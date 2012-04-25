
#ifndef TESTMODEL_H_
#define TESTMODEL_H_

#include <QStandardItemModel>

class TrackList;

class TestModel : public QStandardItemModel {

	Q_OBJECT

	public:
		enum SortingMode {
			SortByFolder,
			SortByArtist,
		};
		TestModel(QObject *parent = 0);
		void populate(const TrackList *);
		void setSortingMode(SortingMode);
	private:
		TrackList *trackList;
		SortingMode sortingMode;

};

#endif
