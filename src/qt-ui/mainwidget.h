
#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QWidget>

class Workspace;
//class EditWidget;
//class PlayWidget;
class QGridLayout;
class QPushButton;

class MainWidget : public QWidget {
	public:
		MainWidget(QWidget *parent = 0);
		void setWorkspace(Workspace *wsp);
	private:
		Workspace   *wsp;
		QGridLayout *layout;
		QPushButton *editModeButton;
};

#endif
