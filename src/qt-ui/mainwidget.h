
#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QWidget>

class Workspace;
// class EditWidget;
class PlayWidget;
// class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;

class MainWidget : public QWidget {

	Q_OBJECT

	public:
		MainWidget(QWidget *parent = 0);
		void setWorkspace(Workspace *wsp);
	private slots:
		void modeButtonClicked(bool);
	private:
		Workspace   *wsp;
		// QGridLayout *layout;
		QVBoxLayout *layout;
		QHBoxLayout *modeButtonLayout;
		QPushButton *modeButton;
		PlayWidget  *playWidget;
};

#endif
