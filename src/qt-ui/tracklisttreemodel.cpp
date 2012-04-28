
#include "tracklisttreemodel.h"

#include <QDirIterator>
#include <QFileInfo>
#include <QString>
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
		<< tr("Sort by Artist")
		<< tr("Sort by Folder"));

TrackListTreeModel::TrackListTreeModel(QObject *parent)
	: QStandardItemModel(parent) {

	trackList   = nullptr;
	sortingMode = SortingMode(0);
}

void TrackListTreeModel::refresh() {
	populate(trackList);
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
		QString artist = t->isValid() ? t->getTag()->artist().toCString() : "missing files";

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
	refresh();
}

QString TrackListTreeModel::getSortingModeText(SortingMode mode) {
	return sortingModeTexts.at(mode);
}

void TrackListTreeModel::addTrack(const QString &path, bool refreshAfterAdd) {
	QLOG_TRACE() << "TrackListTreeModel::addTrack()";
	QLOG_TRACE() << "path:" << path;

	Track *t = new Track(path);
	if (t->isValid()) {
		trackList->append(t);
	} else {
		delete t;
	}
	if (refreshAfterAdd) {
		refresh();
	}
}

/** Adds tracks to the trackList linked to the model.
 * Can be given paths of files and directories. Directories will be scanned
 * recursively for files, and all valid tracks will be added.
 *
 * \param l  a list of absolute paths, which can contain files or directories
 */
void TrackListTreeModel::addTracks(const QStringList &l) {
	QLOG_TRACE() << "TrackListTreeModel::addTracks()";
	for (int i = 0; i < l.length(); i++) {
		QString itemPath = l.at(i);

		if (QFileInfo(itemPath).isFile()) {
			addTrack(itemPath, false);
		} else {
			// for each directory in list, scan subdirectories for files
			QDirIterator iterator(itemPath, QDirIterator::Subdirectories);
			while (iterator.hasNext()) {
				iterator.next();
				itemPath = iterator.filePath();
				if (QFileInfo(itemPath).isFile()) {
					addTrack(itemPath, false);
				}
			}
		}
	}

	refresh();
}
