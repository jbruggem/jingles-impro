
#include "mainwidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QTimer>
#include <QStackedWidget>
#include "QsLog.h"
#include "workspace.h"
#include "nullptr.h"
#include "playwidget.h"
#include "editwidget.h"

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent),
	  wsp(nullptr) {
	QLOG_TRACE() << "MainWidget::MainWidget()";

	// initialise mode button
	modeButton = new QPushButton(tr("Play Mode"));
	modeButton->setCheckable(true);
	connect(modeButton, SIGNAL(clicked(bool)), this, SLOT(modeButtonClicked(bool)));

	// initialise play and edit widgets
	playWidget = new PlayWidget(3);
	editWidget = new EditWidget;
	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget(playWidget);
	stackedWidget->addWidget(editWidget);

	// set up the layout
	layout           = new QVBoxLayout;
	modeButtonLayout = new QHBoxLayout;
	modeButtonLayout->addWidget(modeButton, 0, Qt::AlignRight);
	layout->addLayout(modeButtonLayout);
	layout->addWidget(stackedWidget);
	layout->addStretch();

	setLayout(layout);

	// QTimer::singleShot(3000, this, SLOT(doSth()));

}

void MainWidget::setWorkspace(Workspace *wsp) {
	QLOG_TRACE() << "MainWidget::setWorkspace()";
	this->wsp = wsp;
	playWidget->update(*(wsp->getPlaylist()));
}

void MainWidget::modeButtonClicked(bool checked) {
	QLOG_TRACE() << "MainWidget::modeButtonClicked() " << "checked: " << (checked ? "true" : "false");
	if (checked) {
		modeButton->setText(tr("Edit Mode"));
		stackedWidget->setCurrentWidget(editWidget);
	} else {
		modeButton->setText(tr("Play Mode"));
		stackedWidget->setCurrentWidget(playWidget);
	}
}

void MainWidget::doSth() {
	QLOG_TRACE() << "MainWidget::doSth()";
	// scrollArea->stopScrolling();
	// QTimer::singleShot(5000, this, SLOT(doSthElse()));
}

void MainWidget::doSthElse() {
	QLOG_TRACE() << "MainWidget::doSthElse()";
	// scrollArea->startScrolling();
}
