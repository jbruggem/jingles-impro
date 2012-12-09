
#ifndef TRACKLISTTABLEMODEL_H
#define TRACKLISTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class TrackList;

class TrackListTableModel : public QAbstractTableModel {
    
    Q_OBJECT
    
    public:
        TrackListTableModel(QObject * parent = 0);
        void setTrackList(TrackList *);
        void populate(TrackList *l);
        int rowCount (const QModelIndex & parent = QModelIndex()) const;
        int columnCount (const QModelIndex & parent = QModelIndex()) const;
        QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
        QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        
        QModelIndexList moveBack(QModelIndexList &);
        QModelIndexList moveForward(QModelIndexList &);
    
    private:
        enum Fields {
            FILENAME,
            ARTIST,
            PATH,
            NB_FIELDS,
        };
        QStringList headerNames;
        TrackList *list;
        void refresh();
};

#endif

