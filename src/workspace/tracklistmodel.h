#ifndef TRACKLISTMODEL_H
#define TRACKLISTMODEL_H

#include <QAbstractListModel>
#include "tracklist.h"

class TrackListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TrackListModel(TrackList * list, QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    
signals:
    
public slots:

private:
    TrackList * m_list;
    
};

#endif // TRACKLISTMODEL_H
