
#include "playlistwidget.h"

#include <QGridLayout>
#include <QPushButton>
#include "tracklisttablemodel.h"
#include "tracklisttableview.h"
#include "QsLog.h"

PlayListWidget::PlayListWidget(QWidget *parent)
    : QWidget (parent) {
    
    // set up the track list
    model = new TrackListTableModel;
    view  = new TrackListTableView;
    view->setModel(model);
    
    // set up the buttons
    upButton   = new QPushButton(tr("move up"));
    downButton = new QPushButton(tr("move down"));
    
    // make sure no item is selected and disable the buttons
    view->clearSelection();
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
    
    // set up signals and slots
    connect(view->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(refreshButtons()));
    connect(upButton, SIGNAL(clicked()), this, SLOT(upButtonPressed()));
    connect(downButton, SIGNAL(clicked()), this, SLOT(downButtonPressed()));
}

void PlayListWidget::setTrackList(TrackList *list) {
    model->populate(list);
}

void PlayListWidget::refreshButtons() {
    QLOG_TRACE() << "PlayListWidget::refreshButtons()";
    
    QLOG_TRACE() << "selected rows:";
    auto selectedRows = view->selectionModel()->selectedRows();
    for (const auto i : selectedRows) {
        QLOG_TRACE() << i.row() << i.data().toString();
    }
    
    // the up button will be enabled if some of the selected elements can be moved up:
    // - either if the selection is discontinuous
    // - or if the selection does not include the first row
    // the down button will be enabled if some of the selected elements can be moved down:
    // - either if the selection is discontinuous
    // - or if the selection does not include the last row
    
    // are the first an last row selected?
    bool isFirstRowSelected = selectedRows.contains(model->index(0, 0));
    bool isLastRowSelected  = selectedRows.contains(model->index(model->rowCount()-1, 0));
    QLOG_TRACE() << "first row selected?:" << isFirstRowSelected;
    QLOG_TRACE() << "last row selected?: " << isLastRowSelected;
    
    // is the selection continuous?
    bool continuousSelection = true;
    if (not selectedRows.empty()) {
        int min = selectedRows.first().row();  // row with the lowest index
        int max = selectedRows.first().row();  // row with the highest index
        for (const auto i : selectedRows) {
            if (i.row() < min) {
                min = i.row();
            }
            if (i.row() > max) {
                max = i.row();
            }
        }
        
        if (max - min >= selectedRows.length()) {
            continuousSelection = false;
        }
    }
    QLOG_TRACE() << "continuous selection?: " << continuousSelection;
    
    // finally, activate or deactivate the buttons
    if (selectedRows.empty()) {
        upButton->setDisabled(true);
        downButton->setDisabled(true);
    } else {
        if (isFirstRowSelected and continuousSelection) {
            upButton->setDisabled(true);
        } else {
            upButton->setDisabled(false);
        }
        if (isLastRowSelected and continuousSelection) {
            downButton->setDisabled(true);
        } else {
            downButton->setDisabled(false);
        }
    }
}

void PlayListWidget::upButtonPressed() {
    QLOG_TRACE() << "PlayListWidget::upButtonPressed()";
    
    // Get the selected rows
    auto selectedRows = view->selectionModel()->selectedRows();
    // Have the model move them
    model->moveBack(selectedRows);
    
    refreshButtons();
}

void PlayListWidget::downButtonPressed() {
    QLOG_TRACE() << "PlayListWidget::downButtonPressed()";
    
    // Get the selected rows
    auto selectedRows = view->selectionModel()->selectedRows();
    // Have the model move them
    model->moveForward(selectedRows);
    
    refreshButtons();
}

