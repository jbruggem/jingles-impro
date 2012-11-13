
#include "tracklisttableview.h"

#include <QHeaderView>
#include "tracklisttabledelegate.h"

TrackListTableView::TrackListTableView(QWidget *parent)
    : QTableView(parent) {
    
    setItemDelegate(new TrackListTableDelegate);
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setHighlightSections(false);
    horizontalHeader()->setMovable(true);
    
    verticalHeader()->setHighlightSections(false);
    
    setSortingEnabled(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setTabKeyNavigation(false);
}

void TrackListTableView::setModel(QAbstractItemModel *m) {
    
    QTableView::setModel(m);
}
