
#include "tracklisttreeview.h"

TrackListTreeView::TrackListTreeView(QWidget *parent)
	: QTreeView(parent) {
}

void TrackListTreeView::setModel(QAbstractItemModel *m) {
	QTreeView::setModel(m);
	connect(this->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), model(), SLOT(printItem(const QModelIndex &)));
}

