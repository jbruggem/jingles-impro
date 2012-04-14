
#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QWidget>

class Workspace;
class PlayWidget;
class TwoPaneExplorer;
class QVBoxLayout;
class QHBoxLayout;
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
		Workspace   *wsp;
		QVBoxLayout *layout;
		QHBoxLayout *modeButtonLayout;
		QPushButton *modeButton;
		PlayWidget  *playWidget;
		TwoPaneExplorer  *editWidget;
		QStackedWidget *stackedWidget;
};

#endif
