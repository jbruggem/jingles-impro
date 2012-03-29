
#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QWidget>

class Workspace;
// class EditWidget;
class PlayWidget;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLabel;
class AutoScrollArea;

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
		// QGridLayout *layout;
		QVBoxLayout *layout;
		QHBoxLayout *modeButtonLayout;
		QPushButton *modeButton;
		PlayWidget  *playWidget;
		// QScrollArea *scrollArea;
		QLabel      *label;
		AutoScrollArea *scrollArea;
};

#endif
