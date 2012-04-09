
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
		void rightPaneUpdate(const QModelIndex &);
		void rightPaneSelectFirstRow();
	private:
		QGridLayout *layout;
		QFileSystemModel *dirsOnlyModel;
		QFileSystemModel *fileModel;
		QTreeView *leftPane;
		QTreeView *rightPane;
};

#endif
