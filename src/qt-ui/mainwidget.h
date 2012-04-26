
#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QWidget>

class Workspace;
class PlayWidget;
class EditWidget;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QStackedWidget;

class MainWidget : public QWidget {

	Q_OBJECT

	public:
		MainWidget(QWidget *parent = 0);
		void setWorkspace(Workspace *wsp);
	private slots:
		void modeButtonClicked(bool);
		void doSth();
		void doSthElse();
	private:
		bool playMode;
		Workspace   *wsp;
		QVBoxLayout *layout;
		QHBoxLayout *modeButtonLayout;
		QLabel      *modeLabel;
		QPushButton *modeButton;
		PlayWidget  *playWidget;
		EditWidget  *editWidget;
		QStackedWidget *stackedWidget;
};

#endif
