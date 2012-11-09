
#include "tracklisttableview.h"

#include <QHeaderView>

TrackListTableView::TrackListTableView(QWidget *parent)
    : QTableView(parent) {
    
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setHighlightSections(false);
    horizontalHeader()->setMovable(true);
    
    verticalHeader()->setHighlightSections(false);
    
    setSortingEnabled(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TrackListTableView::setModel(QAbstractItemModel *m) {
    
    QTableView::setModel(m);
}
