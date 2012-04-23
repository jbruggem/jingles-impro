
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class TwoPaneExplorer;
class QGridLayout;
class QLabel;
class QTreeView;
class TestModel;
class TrackList;

class EditWidget : public QWidget {

	Q_OBJECT

	public:
		EditWidget(QWidget *parent = 0);
		void update(const TrackList *);
	private:
		QGridLayout     *layout;
		QLabel          *explorerLabel;
		TwoPaneExplorer *explorer;
		QLabel          *stockListLabel;
		QTreeView       *stockListView;
		TestModel       *testModel;
};

#endif
