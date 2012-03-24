
#ifndef PLAYWIDGET_H_
#define PLAYWIDGET_H_

#include <QWidget>

class QGroupBox;
class QGridLayout;
class QHBoxLayout;
class PushButtonWithExtras;

class PlayWidget : public QWidget {

	Q_OBJECT

	public:
		PlayWidget(QWidget *parent = 0);
	private:
		QGridLayout *gridLayout;
		QGroupBox   *groupBox;
		QHBoxLayout *layout;
		PushButtonWithExtras *playButton;
		PushButtonWithExtras *stopButton;
};

#endif
