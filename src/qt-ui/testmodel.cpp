
#include "testmodel.h"

#include <QString>
#include <QFileInfo>
#include "QsLog.h"
#include "tracklist.h"
#include "nullptr.h"

TestModel::TestModel(QObject *parent)
	: QStandardItemModel(parent) {

	trackList   = nullptr;
	sortingMode = SortByFolder;
}

void TestModel::populate(const TrackList *tl) {
	QLOG_TRACE() << "TestModel::populate()";

	clear();

	if (not tl) {
		QLOG_TRACE() << "TrackList is nullptr";
		return;
	}
	trackList = const_cast<TrackList *>(tl);

	// QStringList tempList;
	for (int i = 0; i < trackList->length(); i++) {
		Track *t = trackList->at(i);
		QString folder = QFileInfo(t->getPath()).absolutePath();

		QLOG_TRACE() << "Track" << i << t->getPath();
		QLOG_TRACE() << "Directory:" << folder;

		QList<QStandardItem *> l = findItems(folder);
		QStandardItem *parentItemPtr = nullptr;
		bool folderAlreadyInModel = false;

		for (int i = 0; i < l.length(); i++) {
			if (not l.at(i)->parent()) {
				folderAlreadyInModel = true;
				parentItemPtr = l.at(i);
				break;
			}
		}
		if (not folderAlreadyInModel) {
			parentItemPtr = new QStandardItem(folder);
			appendRow(parentItemPtr);
		}
		parentItemPtr->appendRow(new QStandardItem(QFileInfo(t->getPath()).fileName()));
	}
}

void TestModel::setSortingMode(SortingMode mode) {
	QLOG_TRACE() << "TestModel::setSortingMode()";
	if (mode == sortingMode) {
		return;
	}
	sortingMode = mode;
	populate(trackList);
}
