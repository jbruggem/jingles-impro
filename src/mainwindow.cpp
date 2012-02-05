
#include "mainwindow.h"

#include "QsLog.h"
#include "buttonpanel.h"

MainWindow::MainWindow() {
	buttonPanel = new ButtonPanel(QStringList() << "one" << "two");
	setCentralWidget(buttonPanel);
}
