
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class QComboBox;
class QGroupBox;
class QPushButton;
class QSplitter;
class QTreeView;
class TrackListTreeModel;
class TrackList;
class TwoPaneExplorer;

class EditWidget : public QWidget {

	Q_OBJECT

	public:
		EditWidget(QWidget *parent = 0);
		void update(const TrackList *);
	private:
		QGroupBox       *explorerGroupBox;
		QGroupBox       *stockListGroupBox;
		QSplitter       *splitter;
		QPushButton     *addButton;
		QTreeView       *stockListView;
		QComboBox       *stockListCBox;
		TrackListTreeModel       *trackListModel;
		TwoPaneExplorer *explorer;
};

#endif
