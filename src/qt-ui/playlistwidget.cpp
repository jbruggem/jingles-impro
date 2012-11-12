
#include "playlistwidget.h"

#include <QGridLayout>
#include "tracklisttablemodel.h"
#include "tracklisttableview.h"
#include <QPushButton>

PlayListWidget::PlayListWidget(QWidget *parent)
    : QWidget (parent) {
    
    // set up the track list
    model = new TrackListTableModel;
    view  = new TrackListTableView;
    view->setModel(model);
    
    // set up the buttons
    upButton   = new QPushButton(tr("move up"));
    downButton = new QPushButton(tr("move down"));
    
    upButton->setDisabled(true);
    downButton->setDisabled(true);
    
    // set up the layout
    QGridLayout *l = new QGridLayout;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(upButton);
    buttonLayout->addWidget(downButton);
    buttonLayout->addStretch();
    l->addWidget(view, 0, 0);
    l->addLayout(buttonLayout, 0, 1);
    l->setContentsMargins(0, 0, 0, 0);
    setLayout(l);
}

void PlayListWidget::setTrackList(const TrackList *list) {
    model->populate(list);
}

