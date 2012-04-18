
#ifndef EDITWIDGET_H_
#define EDITWIDGET_H_

#include <QWidget>

class TwoPaneExplorer;
class QGridLayout;
class QLabel;
class QListWidget;

class EditWidget : public QWidget {

	Q_OBJECT

	public:
		EditWidget(QWidget *parent = 0);
	private:
		QGridLayout     *layout;
		QLabel          *explorerLabel;
		TwoPaneExplorer *explorer;
		QLabel          *stockListLabel;
		QListWidget     *stockListView;
};

#endif
