
#include "mainwidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStringList>
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
	setLayout(layout);
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
