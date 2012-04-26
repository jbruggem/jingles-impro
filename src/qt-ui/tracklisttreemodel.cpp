
#include "tracklisttreemodel.h"

#include <QString>
#include <QFileInfo>
#include "QsLog.h"
#include "tracklist.h"
#include "nullptr.h"

// enum SortingMode {
// 	SortByArtist,
// 	SortByFolder,
// 	NbSortingModes,
// };

QStringList TrackListTreeModel::sortingModeTexts =
		(QStringList()
		<< "Sort by Artist"
		<< "Sort by Folder");

TrackListTreeModel::TrackListTreeModel(QObject *parent)
	: QStandardItemModel(parent) {

	trackList   = nullptr;
	sortingMode = SortingMode(0);
}

void TrackListTreeModel::populate(const TrackList *tl) {
	QLOG_TRACE() << "TestModel::populate()";

	clear();

	if (not tl) {
		QLOG_TRACE() << "TrackList is nullptr";
		return;
	}
	trackList = const_cast<TrackList *>(tl);

	for (int i = 0; i < trackList->length(); i++) {
		Track *t = trackList->at(i);
		QString folder = QFileInfo(t->getPath()).absolutePath();
		QString artist = t->exists() ? t->getTag()->artist().toCString() : "missing files";

		QString parent;
		switch (sortingMode) {
			case SortByFolder:
				parent = folder;
				break;
			case SortByArtist:
				parent = artist;
				break;
			default:
				parent = folder;
				break;
		}

		QLOG_TRACE() << "Track" << i << t->getPath();
		QLOG_TRACE() << "Directory:" << folder;
		QLOG_TRACE() << "Artist   :" << artist;

		QList<QStandardItem *> l = findItems(parent);
		QStandardItem *parentItemPtr = nullptr;
		bool parentAlreadyInModel = false;

		for (int i = 0; i < l.length(); i++) {
			if (not l.at(i)->parent()) {
				parentAlreadyInModel = true;
				parentItemPtr = l.at(i);
				break;
			}
		}
		if (not parentAlreadyInModel) {
			parentItemPtr = new QStandardItem(parent);
			appendRow(parentItemPtr);
		}
		parentItemPtr->appendRow(new QStandardItem(QFileInfo(t->getPath()).fileName()));
	}
}

void TrackListTreeModel::setSortingMode(int m) {
	setSortingMode(SortingMode(m));
}
void TrackListTreeModel::setSortingMode(SortingMode mode) {
	QLOG_TRACE() << "TestModel::setSortingMode()";
	if (mode == sortingMode) {
		return;
	}
	sortingMode = mode;
	populate(trackList);
}

QString TrackListTreeModel::getSortingModeText(SortingMode mode) {
	return sortingModeTexts.at(mode);
}
