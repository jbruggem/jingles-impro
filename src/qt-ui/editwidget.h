
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class QComboBox;
class QGroupBox;
class QPushButton;
class QSplitter;
class TrackListTreeModel;
class TrackListTreeView;
class TrackList;
class TwoPaneExplorer;

class EditWidget : public QWidget {

	Q_OBJECT

	public:
		EditWidget(QWidget *parent = 0);
		void update(const TrackList *);
	private slots:
		void addButtonClicked();
	private:
		QGroupBox          *explorerGroupBox;
		QGroupBox          *stockListGroupBox;
		QSplitter          *splitter;
		QPushButton        *addButton;
		TrackListTreeView  *stockListView;
		QComboBox          *stockListCBox;
		TrackListTreeModel *trackListModel;
		TwoPaneExplorer    *explorer;
};

#endif
