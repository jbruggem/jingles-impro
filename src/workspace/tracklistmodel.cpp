#include "tracklistmodel.h"

TrackListModel::TrackListModel(TrackList * list,QObject *parent) :
    QAbstractListModel(parent),
    m_list(list)
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
    if(!parent.isValid())
        return m_list->length();
    else return 0;
}
