
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

//	QStandardItem *parentItem = invisibleRootItem();
//	for (int i = 0; i < 4; ++i) {
//		QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
//		parentItem->appendRow(item);
//		parentItem = item;
//	}
}

void TestModel::populate(const TrackList *tl) {
	QLOG_TRACE() << "TestModel::populate()";
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
		QLOG_TRACE() << l.length() << "items in model that match" << folder;
		for (int i = 0; i < l.length(); i++) {
			QLOG_TRACE() << l.at(i)->text();
			QLOG_TRACE() << "l.at(i)->parent()?" << (l.at(i)->parent() ? "yes": "no");
		}
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
	sortingMode = mode;
}

void TestModel::clear() {

}
