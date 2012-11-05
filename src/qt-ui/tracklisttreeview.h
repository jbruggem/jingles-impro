
#ifndef TRACKLISTTREEVIEW_H_
#define TRACKLISTTREEVIEW_H_

#include <QTreeView>

class TrackListTreeView : public QTreeView {

	Q_OBJECT

	public:
		TrackListTreeView(QWidget *parent = 0);
		virtual void setModel(QAbstractItemModel *);
};

#endif
