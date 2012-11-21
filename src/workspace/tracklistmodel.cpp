#include "tracklistmodel.h"

TrackListModel::TrackListModel(TrackList * list,QObject *parent) :
    m_list(list),
    QAbstractListModel(parent)
{
}


QVariant TrackListModel::data(const QModelIndex &index, int role)  const{
    if (role == Qt::DisplayRole)
    {
        return m_list->at(index.row())->getDisplayName();
    }
    return QVariant();
}

int TrackListModel::rowCount(const QModelIndex &parent) const{
    return m_list->length();
}
