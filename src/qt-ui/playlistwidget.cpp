
#include "playlistwidget.h"

#include <QGridLayout>
#include "tracklisttablemodel.h"
#include "tracklisttableview.h"

PlayListWidget::PlayListWidget(QWidget *parent)
    : QWidget (parent) {
    
    // set up the track list
    model = new TrackListTableModel;
    view  = new TrackListTableView;
    view->setModel(model);
    
    // set up the layout
    setLayout(new QGridLayout);
    layout()->addWidget(view);
    layout()->setContentsMargins(0, 0, 0, 0);
}

void PlayListWidget::setTrackList(const TrackList *list) {
    model->populate(list);
}

