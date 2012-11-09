
#ifndef STOCKLISTWIDGET_H
#define STOCKLISTWIDGET_H

#include <QWidget>

class QComboBox;
class TrackListTreeModel;
class TrackListTreeView;
class TrackList;

class StockListWidget: public QWidget {
    
    Q_OBJECT
    
    public:
        StockListWidget(QWidget *parent = 0);
        void setTrackList(const TrackList *);
    private:
        TrackListTreeView  *view;
        TrackListTreeModel *model;
        QComboBox          *filterCBox;
};

#endif

