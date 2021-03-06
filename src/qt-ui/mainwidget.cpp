
#include "mainwidget.h"

MainWidget::MainWidget(UiController * controller, QWidget *parent)
	: QWidget(parent),
	  wsp(nullptr),
	  controller(controller) {
	QLOG_TRACE() << "MainWidget::MainWidget()";

	playMode = true;

    // debug layout
//    QPalette p(palette());
//    p.setColor(QPalette::Background, Qt::red);
//    setPalette(p);
//    setAutoFillBackground(true);

	// initialise mode label and button
	modeLabel  = new QLabel(tr("Play Mode"));
    modeButton = new QPushButton(tr("Switch"));
    connect(modeButton, SIGNAL(clicked()), this, SLOT(modeButtonClicked()));

    stopAllButton = new QPushButton(tr("Stop All"));
    connect(stopAllButton, SIGNAL(clicked()), controller, SLOT(stopAllButtonClicked()));

    stopAllShortcut = new QShortcut(QKeySequence("Ctrl+s"), this);
    connect(stopAllShortcut,SIGNAL(activated()),controller,SLOT(stopAllButtonClicked()));


	// initialise play and edit widgets
    playWidget = new PlayWidget(controller,3);
	editWidget = new EditWidget;
	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget(playWidget);
	stackedWidget->addWidget(editWidget);

	// set up the layout
	layout           = new QVBoxLayout;
	modeButtonLayout = new QHBoxLayout;
	modeButtonLayout->addStretch();
    modeButtonLayout->addWidget(stopAllButton, 0, Qt::AlignRight);
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
    playWidget->update(wsp->getButtonlist(),wsp->getPlaylist());
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
