
#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>

class TrackListTableModel;
class TrackListTableView;
class TrackList;
class QPushButton;

class PlayListWidget: public QWidget {
    
    Q_OBJECT
    
    public:
        PlayListWidget(QWidget *parent = 0);
        void setTrackList(const TrackList *);
    private slots:
        void refreshButtons();
    private:
        TrackListTableModel *model;
        TrackListTableView  *view;
        QPushButton *upButton;
        QPushButton *downButton;
};

#endif

