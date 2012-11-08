
#include "tracklisttreemodel.h"

#include <QDirIterator>
#include <QFileInfo>
#include <QString>
#include "QsLog.h"

QMap<TrackListTreeModel::SortingMode, QString> TrackListTreeModel::sortingModeTexts = getSortingModeTexts();

QMap<TrackListTreeModel::SortingMode, QString> TrackListTreeModel::getSortingModeTexts() {
	QMap<SortingMode, QString> map;
	map[SortByArtist] = "Sort by Artist";
	map[SortByFolder] = "Sort by Folder";
	return map;
}

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

	// todo merge these two lines by directly subclassing QAbstractItemModel
	clear();
	sortedTrackList.clear();

	if (not tl) {
		QLOG_TRACE() << "TrackList is nullptr";
		return;
	}
	trackList = const_cast<TrackList *>(tl);

	// map used for sorting items
	// first field is the one we are sorting by
	// second field is the file name
	// third field is the number of times the same file name appears
	QMap<QString, QMap<QString, int> > map;

	// fill the sorting map
	switch(sortingMode) {
		case SortByArtist:
			for (int i = 0; i < trackList->length(); i++) {
				Track *t = trackList->at(i);
				QString fileName = QFileInfo(t->getPath()).fileName();
                QString artist = t->isValid() ? *t->getArtist() : tr(".missing files");
				if (artist.isEmpty()) {
					artist = ".unknown";
				}
				if (not map[artist].contains(fileName)) {
					map[artist][fileName] = 1;
				} else {
					map[artist][fileName]++;
				}
			}
			break;
		case SortByFolder:
			for (int i = 0; i < trackList->length(); i++) {
				Track *t = trackList->at(i);
				QString fileName = QFileInfo(t->getPath()).fileName();
				QString folder = QFileInfo(t->getPath()).absolutePath();
				if (not map[folder].contains(fileName)) {
					map[folder][fileName] = 1;
				} else {
					map[folder][fileName]++;
				}
			}
			break;
		default:
			break;
	}

	// populate the model
	foreach(QString key, map.keys()) {
		QStandardItem *parent = new QStandardItem(key);
		appendRow(parent);

		foreach(QString fileName, map[key].keys()) {
			for (int i = 0; i < map[key][fileName]; i++) {
				parent->appendRow(new QStandardItem(fileName));
			}
		}
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
	return sortingModeTexts[mode];
}

void TrackListTreeModel::addTrack(const QString &path) {
	addTrack(path, true);
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

Track *TrackListTreeModel::getTrack(const QModelIndex &) const {
}

void TrackListTreeModel::printItem(const QModelIndex &index) const {
	QLOG_TRACE() << "TrackListTreeModel::printItem()";
	QLOG_INFO() << "data:" << index.data().toString();
}
