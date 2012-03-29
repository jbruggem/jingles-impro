
#include "mainwidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QScrollArea>
#include <QLabel>
#include <QTimer>
#include <QScrollBar>
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

	// test scrolling label
	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(scroll()));
	timer->setSingleShot(true);
	timer->start(1000);
	scrollArea = new QScrollArea;
	label = new QLabel("A scroll area is used to display the contents of a child widget within a frame. If the widget exceeds the size of the frame, the view can provide scroll bars so that the entire area of the child widget can be viewed. The child widget must be specified with setWidget().");
	scrollArea->setWidget(label);
	// scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	// scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	layout->addWidget(scrollArea);

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

void MainWidget::scroll() {
	QLOG_TRACE() << "MainWidget::scroll()";
	QLOG_INFO() << "horizontalScrollBar  min =" << scrollArea->horizontalScrollBar()->minimum();
	QLOG_INFO() << "horizontalScrollBar  max =" << scrollArea->horizontalScrollBar()->maximum();
	enum stateEnum {
		StartPosition,
		ScrollingRight,
		ScrollingLeft,
		EndPosition
	};
	static stateEnum state = StartPosition;
	switch(state) {
		case StartPosition:
			timer->start(1000);
			state = ScrollingRight;
			break;
		case ScrollingRight:
			if (scrollArea->horizontalScrollBar()->value() < scrollArea->horizontalScrollBar()->maximum()) {
				scrollArea->horizontalScrollBar()->setValue(scrollArea->horizontalScrollBar()->value()+1);
			} else {
				state = EndPosition;
			}
			timer->start(10);
			break;
		case ScrollingLeft:
			if (scrollArea->horizontalScrollBar()->value() > scrollArea->horizontalScrollBar()->minimum()) {
				scrollArea->horizontalScrollBar()->setValue(scrollArea->horizontalScrollBar()->value()-1);
			} else {
				state = StartPosition;
			}
			timer->start(10);
			break;
		case EndPosition:
			timer->start(500);
			state = ScrollingLeft;
			break;
	}
	QLOG_INFO() << "horizontalScrollBar  value =" << scrollArea->horizontalScrollBar()->value();
}
