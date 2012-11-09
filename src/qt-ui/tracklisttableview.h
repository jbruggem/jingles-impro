
#ifndef TRACKLISTTABLEVIEW_H_
#define TRACKLISTTABLEVIEW_H_

#include <QTableView>

class TrackListTableView : public QTableView {

	Q_OBJECT

	public:
		TrackListTableView(QWidget *parent = 0);
		virtual void setModel(QAbstractItemModel *);
};

#endif
