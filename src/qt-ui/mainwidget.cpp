
#include "mainwidget.h"

#include <QGridLayout>
#include <QPushButton>
#include "QsLog.h"
#include "workspace.h"
#include "nullptr.h"
#include "playwidget.h"

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent),
	  wsp(nullptr) {
	QLOG_TRACE() << "MainWidget::MainWidget()";

	// initialise mode button
	modeButton = new QPushButton(tr("Play Mode"));
	modeButton->setCheckable(true);
	connect(modeButton, SIGNAL(clicked(bool)), this, SLOT(modeButtonClicked(bool)));

	// initialise play widget
	playWidget = new PlayWidget;

	// set up the layout
	layout = new QGridLayout;
	layout->addWidget(modeButton, 1, 2, Qt::AlignRight);
	layout->addWidget(playWidget, 2, 1, 1, 2);
	setLayout(layout);
}

void MainWidget::setWorkspace(Workspace *wsp) {
	QLOG_TRACE() << "MainWidget::setWorkspace()";
	this->wsp = wsp;
}

void MainWidget::modeButtonClicked(bool checked) {
	QLOG_TRACE() << "MainWidget::modeButtonClicked() " << "checked: " << (checked ? "true" : "false");
	modeButton->setText(checked ? tr("Edit Mode") : tr("Play Mode"));
}
