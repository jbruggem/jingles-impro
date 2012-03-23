
#include "basicui.h"

#include "QsLog.h"
#include "mainwidget.h"
#include "workspace.h"

BasicUi::BasicUi(QWidget *parent)
    : QMainWindow(parent) {
	QLOG_TRACE() << "BasicUi::BasicUi()";
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
}

void BasicUi::setWorkspace(Workspace *wsp) {
	QLOG_TRACE() << "BasicUi::setWorkspace()";
    mainWidget->setWorkspace(wsp);
}
