
#include "stocklistwidget.h"

#include <QComboBox>
#include <QGridLayout>
#include "tracklisttreemodel.h"
#include "tracklisttreeview.h"

StockListWidget::StockListWidget(QWidget *parent)
    : QWidget (parent) {
    
    // set up the track list
    model = new TrackListTreeModel;
    view  = new TrackListTreeView;
    view->setModel(model);
    view->setHeaderHidden(true);
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    
    // set up the filter combo box
    filterCBox = new QComboBox;
    for (int i = 0; i < TrackListTreeModel::NbSortingModes; i++) {
        filterCBox->addItem(TrackListTreeModel::getSortingModeText(TrackListTreeModel::SortingMode(i)));
    }
    
    // set up the layout
    setLayout(new QGridLayout);
    layout()->addWidget(view);
    layout()->addWidget(filterCBox);
    layout()->setContentsMargins(0, 0, 0, 0);
    
    // connect signals and slots
    connect(filterCBox, SIGNAL(currentIndexChanged(int)), model, SLOT(setSortingMode(int)));
}

void StockListWidget::setTrackList(const TrackList *list) {
    model->populate(list);
}

