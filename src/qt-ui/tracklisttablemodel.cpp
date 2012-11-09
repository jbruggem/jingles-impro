
#include "tracklisttablemodel.h"

#include <QDirIterator>
#include <QFileInfo>
#include <QString>
#include <QList>
#include "QsLog.h"

TrackListTableModel ::TrackListTableModel (QObject *parent)
    : QStandardItemModel(parent) {

    trackList   = nullptr;
}

void TrackListTableModel::initHeader() {
    setHorizontalHeaderLabels(QStringList() << "File Name" << "Artist" << "Path");
}

void TrackListTableModel ::refresh() {
    populate(trackList);
}

void TrackListTableModel ::populate(const TrackList *tl) {
    QLOG_TRACE() << "TestModel::populate()";
    
    clear();
    initHeader();

    if (not tl) {
        QLOG_TRACE() << "TrackList is nullptr";
        return;
    }
    trackList = const_cast<TrackList *>(tl);

    for (int i = 0; i < trackList->length(); i++) {
        Track *t = trackList->at(i);
        QString path     = t->getPath();
        QString fileName = QFileInfo(path).fileName();
        QString artist   = t->isValid() ? *t->getArtist() : tr(".missing files");
        if (artist.isEmpty()) {
            artist = ".unknown";
        }
        QList<QStandardItem *> items;
        items.append(new QStandardItem(fileName));
        items.append(new QStandardItem(artist));
        items.append(new QStandardItem(path));
        
        this->appendRow(items);
    }
}

void TrackListTableModel ::addTrack(const QString &path) {
    addTrack(path, true);
}

void TrackListTableModel ::addTrack(const QString &path, bool refreshAfterAdd) {
    QLOG_TRACE() << "TrackListTableModel ::addTrack()";
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
void TrackListTableModel ::addTracks(const QStringList &l) {
    QLOG_TRACE() << "TrackListTableModel ::addTracks()";
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

