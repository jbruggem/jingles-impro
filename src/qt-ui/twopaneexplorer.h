
#ifndef TWOPANEEXPLORER_H_
#define TWOPANEEXPLORER_H_

#include <QWidget>

class QFileSystemModel;
class QLabel;
class QLineEdit;
class QModelIndex;
class QShortcut;
class QSplitter;
class QString;
class QTimer;
class QTreeView;
#include "history.h"

class TwoPaneExplorer : public QWidget {

	Q_OBJECT

	public:
		TwoPaneExplorer(QWidget *parent = 0);
		void setRefreshDelay(int);
		int  getRefreshDelay() const;
		void setBackspaceToHistoryBack(bool);
		bool isBackspaceHistoryBack() const;
		QStringList getSelection() const;
		QStringList getFilterList() const;
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
		void filterChanged();
	private:
		QSplitter        *paneSplitter;
		QFileSystemModel *dirsOnlyModel;
		QFileSystemModel *fileModel;
		QTreeView   *leftPane;
		QTreeView   *rightPane;
		QLabel      *filterLabel;
		QLineEdit   *filterEditor;
		QTimer      *refreshDelayTimer;
		int          refreshDelay;
		QString      leftPaneFolder;
		QShortcut   *shortcut_backspace;
		QShortcut   *shortcut_altLeft;
		QShortcut   *shortcut_altRight;
		QShortcut   *shortcut_altUp;
		History      history;
		bool backspaceIsHistoryBack;
};

#endif
