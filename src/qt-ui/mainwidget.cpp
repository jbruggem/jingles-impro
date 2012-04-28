
#include "mainwidget.h"

#include <QVBoxLayout>
#include <QLabel>
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

	playMode = true;

	// initialise mode label and button
	modeLabel  = new QLabel(tr("Play Mode"));
	modeButton = new QPushButton(tr("Change"));
	connect(modeButton, SIGNAL(clicked()), this, SLOT(modeButtonClicked()));

	// initialise play and edit widgets
	playWidget = new PlayWidget(3);
	editWidget = new EditWidget;
	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget(playWidget);
	stackedWidget->addWidget(editWidget);

	// set up the layout
	layout           = new QVBoxLayout;
	modeButtonLayout = new QHBoxLayout;
	modeButtonLayout->addStretch();
	modeButtonLayout->addWidget(modeLabel, 0, Qt::AlignRight);
	modeButtonLayout->addWidget(modeButton, 0, Qt::AlignRight);
	layout->addLayout(modeButtonLayout);
	layout->addWidget(stackedWidget);
	// layout->addStretch();

	setLayout(layout);

	// QTimer::singleShot(3000, this, SLOT(doSth()));

}

void MainWidget::setWorkspace(Workspace *wsp) {
	QLOG_TRACE() << "MainWidget::setWorkspace()";
	this->wsp = wsp;
	playWidget->update(wsp->getPlaylist());
	editWidget->update(wsp->getStock());
}

void MainWidget::modeButtonClicked() {
	QLOG_TRACE() << "MainWidget::modeButtonClicked()";

	playMode = not playMode;
	if (playMode) {
		modeLabel->setText(tr("Play Mode"));
		stackedWidget->setCurrentWidget(playWidget);
	} else {
		modeLabel->setText(tr("Edit Mode"));
		stackedWidget->setCurrentWidget(editWidget);
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
