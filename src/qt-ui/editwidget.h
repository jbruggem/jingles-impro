
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class QComboBox;
class QGroupBox;
class QLabel;
class QSplitter;
class QTreeView;
class TestModel;
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
		QTreeView       *stockListView;
		QComboBox       *stockListCBox;
		TestModel       *testModel;
		TwoPaneExplorer *explorer;
};

#endif
