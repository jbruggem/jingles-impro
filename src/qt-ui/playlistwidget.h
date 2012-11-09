
#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>

class TrackListTableModel;
class TrackListTableView;
class TrackList;

class PlayListWidget: public QWidget {
    
    Q_OBJECT
    
    public:
        PlayListWidget(QWidget *parent = 0);
        void setTrackList(const TrackList *);
    private:
        TrackListTableModel *model;
        TrackListTableView  *view;
};

#endif

