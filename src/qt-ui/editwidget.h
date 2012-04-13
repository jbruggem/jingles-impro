
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class QGridLayout;
class QFileSystemModel;
class QTreeView;
class QModelIndex;
class QTimer;
class QString;
class QShortcut;
#include "history.h"

class EditWidget : public QWidget {

	Q_OBJECT

	public:
		EditWidget(QWidget *parent = 0);
		void setRefreshDelay(int);
		int  getRefreshDelay() const;
		void setBackspaceToHistoryBack(bool);
		bool isBackspaceHistoryBack() const;
	public slots:
		void leftPaneUpdate(const QString &);
		void rightPaneUpdate(const QString &);
		void navigateUp();
		void navigateBack();
		void navigateForward();
	private slots:
		void rightPaneItemActivated(const QModelIndex &);
		void leftPaneItemSelected(const QModelIndex &);
		void rightPaneUpdate();
		void rightPaneUpdated();
		void rightPaneSelectFirstRow();
	private:
		QGridLayout      *layout;
		QFileSystemModel *dirsOnlyModel;
		QFileSystemModel *fileModel;
		QTreeView *leftPane;
		QTreeView *rightPane;
		QTimer    *refreshDelayTimer;
		int        refreshDelay;
		QString    leftPaneFolder;
		QShortcut   *shortcut_backspace;
		QShortcut   *shortcut_altLeft;
		QShortcut   *shortcut_altRight;
		QShortcut   *shortcut_altUp;
		History      history;
		bool backspaceIsHistoryBack;
};

#endif
