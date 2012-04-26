
#ifndef TESTMODEL_H_
#define TESTMODEL_H_

#include <QStandardItemModel>
#include <QStringList>

class TrackList;

class TestModel : public QStandardItemModel {

	Q_OBJECT

	public:
		enum SortingMode {
			SortByArtist,
			SortByFolder,
			NbSortingModes,
		};
		TestModel(QObject *parent = 0);
		void populate(const TrackList *);
		static QString getSortingModeText(SortingMode);
		void setSortingMode(SortingMode);
	public slots:
		void setSortingMode(int);
	private:
		TrackList *trackList;
		SortingMode sortingMode;
		static QStringList sortingModeTexts;
};

#endif
