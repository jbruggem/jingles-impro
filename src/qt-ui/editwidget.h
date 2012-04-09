
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class QGridLayout;
class QFileSystemModel;
class QTreeView;
class QModelIndex;

class EditWidget : public QWidget {

	Q_OBJECT

	public:
		EditWidget(QWidget *parent = 0);
	public slots:
		void leftPaneSelectionChanged(const QModelIndex &);
	private:
		QGridLayout *layout;
		QFileSystemModel *dirsOnlyModel;
		QFileSystemModel *fileModel;
		QTreeView *leftPane;
		QTreeView *rightPane;
};

#endif
