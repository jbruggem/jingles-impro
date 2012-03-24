
#ifndef PLAYWIDGET_H_
#define PLAYWIDGET_H_

#include <QWidget>

class QGridLayout;
class PlayWidgetEntry;

class PlayWidget : public QWidget {

	Q_OBJECT

	public:
		PlayWidget(QWidget *parent = 0);
	private:
		QGridLayout     *gridLayout;
		PlayWidgetEntry *trackEntry;
};

#endif
