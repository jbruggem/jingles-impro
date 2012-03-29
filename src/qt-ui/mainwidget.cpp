
#include "mainwidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QLabel>
#include <QTimer>
#include <QScrollBar>
#include "QsLog.h"
#include "workspace.h"
#include "nullptr.h"
#include "playwidget.h"
#include "autoscrollarea.h"

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent),
	  wsp(nullptr) {
	QLOG_TRACE() << "MainWidget::MainWidget()";

	// initialise mode button
	modeButton = new QPushButton(tr("Play Mode"));
	modeButton->setCheckable(true);
	connect(modeButton, SIGNAL(clicked(bool)), this, SLOT(modeButtonClicked(bool)));

	// initialise play widget
	playWidget = new PlayWidget(3);

	// set up the layout
	layout           = new QVBoxLayout;
	modeButtonLayout = new QHBoxLayout;
	// layout = new QGridLayout;
	// layout->addWidget(modeButton, 0, 1, Qt::AlignRight);
	// layout->addWidget(playWidget, 1, 0, 1, 2);
	modeButtonLayout->addWidget(modeButton, 0, Qt::AlignRight);
	layout->addLayout(modeButtonLayout);
	layout->addWidget(playWidget);
	layout->addStretch();

	scrollArea = new AutoScrollArea;
	label = new QLabel("A scroll area is used to display the contents of a child widget within a frame. If the widget exceeds the size of the frame, the view can provide scroll bars so that the entire area of the child widget can be viewed.");
	scrollArea->setWidget(label);
	scrollArea->setMode(AutoScrollArea::OneTimeOneWay);
	scrollArea->setRewindAfterScroll(true);
	scrollArea->setTimings(30, 1, 1000);
	scrollArea->startScrolling();
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	layout->addWidget(scrollArea);

	setLayout(layout);

	QTimer::singleShot(5000, this, SLOT(doSth()));

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
		playWidget->hide();
	} else {
		modeButton->setText(tr("Play Mode"));
		playWidget->show();
	}
}

void MainWidget::doSth() {
	QLOG_TRACE() << "MainWidget::doSth()";
	scrollArea->pauseScrolling();
	QTimer::singleShot(5000, this, SLOT(doSthElse()));
}

void MainWidget::doSthElse() {
	QLOG_TRACE() << "MainWidget::doSthElse()";
	scrollArea->startScrolling();
}
