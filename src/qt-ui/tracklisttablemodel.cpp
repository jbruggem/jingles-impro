
#include "tracklisttablemodel.h"

#include "tracklist.h"
#include "QsLog.h"

TrackListTableModel ::TrackListTableModel (QObject * parent)
    : QAbstractTableModel(parent) {
    list = nullptr;
    
    headerNames = {"File Name", "Artist", "Path"};
}

void TrackListTableModel::refresh() {
    setTrackList(list);
}

void TrackListTableModel::populate(TrackList *l) {
    setTrackList(l);
}

void TrackListTableModel::setTrackList(TrackList *l) {
    beginResetModel();
    list = l;
    endResetModel();
}

int TrackListTableModel::rowCount(const QModelIndex & parent) const {
    if(parent.isValid() or not list) {
        return 0;
    }
    return list->length();
}

int TrackListTableModel::columnCount(const QModelIndex & parent) const {
    if(parent.isValid() or not list) {
        return 0;
    }
    return NB_FIELDS;
}

QVariant TrackListTableModel::headerData (int section, Qt::Orientation orientation, int role) const {
    
    if (orientation == Qt::Horizontal and role == Qt::DisplayRole) {
        if (section >= 0 and section < NB_FIELDS) {
            return headerNames.at(section);
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant TrackListTableModel::data(const QModelIndex & index, int role) const {
    
    if (not list or index.row() < 0 or index.row() >= list->size()) {
        return QVariant();
    }
    
    Track *t = list->at(index.row());
    QString path     = t->getPath();
    QString fileName = QFileInfo(path).fileName();
    QString artist   = t->isValid() ? *t->getArtist() : tr(".missing files");
    
    if (artist.isEmpty()) {
        artist = ".unknown";
    }

    switch (role) {
        case Qt::DisplayRole:
            switch (index.column()) {
                case FILENAME:
                    return fileName;
                case ARTIST:
                    return artist;
                case PATH:
                    return path;
                default:
                    return QVariant();
            }
            break;
    }

    return QVariant();
}

QModelIndexList TrackListTableModel::moveBack(QModelIndexList &indexes) {
    
    // Indexes need to be sorted to make it easier to know how we are
    // iterating over them.
    qSort(indexes);
    
    // This list will contain the new indexes after the move operation.
    QModelIndexList newIndexes;
    
    // we only move back items that:
    // - are not the first item
    // - are not after another item that cannot move
    // The following is an example of this logic:
    // - the list has five items
    // - items 0, 1, 3 and 4 need to be moved back
    // - item 0 cannot move because it is the first
    // - item 1 can also not move because it would displace item 0
    // - item 3 gets moved to index 2
    // - item 4 gets moved to index 3
    for (int i = 0; i < indexes.length(); i++) {
        const auto modelIndex = indexes.at(i);
        int fromRow = modelIndex.row();
        int toRow   = fromRow-1;
        if (fromRow != i) {
            beginMoveRows(modelIndex.parent(), fromRow, fromRow, modelIndex.parent(), toRow);
            
            auto temp = list->takeAt(fromRow);
            list->insert(toRow, temp);
            
            endMoveRows();
            newIndexes.append(index(toRow, 0));
        } else {
            newIndexes.append(index(fromRow, 0));
        }
    }
    
    return newIndexes;
}

QModelIndexList TrackListTableModel::moveForward(QModelIndexList &indexes) {
    
    // Indexes need to be sorted to make it easier to know how we are
    // iterating over them.
    qSort(indexes);
    // beginResetModel();
    
    // This list will contain the new indexes after the move operation.
    QModelIndexList newIndexes;
    
    // we only move forward items that:
    // - are not the last item
    // - are not before another item that cannot move
    // The following is an example of this logic:
    // - the list has five items
    // - items 0, 1, 3 and 4 need to be moved forward
    // - item 4 cannot move because it is last
    // - item 3 can also not move because it would displace item 4
    // - item 1 gets moved to index 2
    // - item 0 gets moved to index 1
    for (int i = 0; i < indexes.length(); i++) {
        const auto modelIndex = indexes.at(indexes.length() - i - 1);
        int fromRow = modelIndex.row();
        int toRow   = fromRow + 1;
        if (fromRow != list->length() - i - 1) {
            // must call beginMoveRows with (toRow+1) because the documentation says:
            // "However, when moving rows down in the same parent [...], the rows will be placed before the destinationChild index."
            beginMoveRows(modelIndex.parent(), fromRow, fromRow, modelIndex.parent(), toRow+1);
            
            auto temp = list->takeAt(fromRow);
            list->insert(toRow, temp);
            
            endMoveRows();
            newIndexes.append(index(toRow, 0));
        } else {
            newIndexes.append(index(fromRow, 0));
        }
    }
    
    return newIndexes;
}

