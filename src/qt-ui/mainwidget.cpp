
#include "mainwidget.h"

#include <QGridLayout>
#include <QPushButton>
#include "QsLog.h"
#include "workspace.h"
#include "nullptr.h"

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent),
	  wsp(nullptr) {
	QLOG_TRACE() << "MainWidget::MainWidget()";

	editModeButton = new QPushButton("push me");
	editModeButton->setCheckable(true);

	layout = new QGridLayout();
	layout->addWidget(editModeButton);
	setLayout(layout);
}

void MainWidget::setWorkspace(Workspace *wsp) {
	QLOG_TRACE() << "MainWidget::setWorkspace()";
	this->wsp = wsp;
}
