
#include "basicui.h"


BasicUi::BasicUi(UiController * controller, QWidget *parent)
    : QMainWindow(parent) {
	QLOG_TRACE() << "BasicUi::BasicUi()";
    mainWidget = new MainWidget(controller);
    setCentralWidget(mainWidget);
}

void BasicUi::setWorkspace(Workspace *wsp) {
	QLOG_TRACE() << "BasicUi::setWorkspace()";
    mainWidget->setWorkspace(wsp);
}
