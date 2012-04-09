
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class QGridLayout;
class QFileSystemModel;
class QTreeView;
class QModelIndex;
class QTimer;

class EditWidget : public QWidget {

	Q_OBJECT

	public:
		EditWidget(QWidget *parent = 0);
	public slots:
		void rightPaneItemActivated(const QModelIndex &);
		void leftPaneItemSelected(const QModelIndex &);
		void leftPaneUpdate(const QString &);
		void rightPaneUpdate(const QString &);
		void rightPaneSelectFirstRow();
	private:
		QGridLayout *layout;
		QFileSystemModel *dirsOnlyModel;
		QFileSystemModel *fileModel;
		QTreeView *leftPane;
		QTreeView *rightPane;
		QTimer *selectionTimer;
};

#endif
