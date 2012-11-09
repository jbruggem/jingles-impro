
#include "tracklisttableview.h"

#include <QHeaderView>

TrackListTableView::TrackListTableView(QWidget *parent)
    : QTableView(parent) {
    
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->hide();
}

void TrackListTableView::setModel(QAbstractItemModel *m) {
    
    QTableView::setModel(m);
}
