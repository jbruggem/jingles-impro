
#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QTimer>
#include <QStackedWidget>
#include "QsLog.h"
#include "workspace.h"
#include "playwidget.h"
#include "editwidget.h"
#include "uicontroller.h"

class MainWidget : public QWidget {

	Q_OBJECT

	public:
        MainWidget(UiController * controller, QWidget *parent = 0);
		void setWorkspace(Workspace *wsp);
	private slots:
		void modeButtonClicked();
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
        UiController * controller;
};

#endif
