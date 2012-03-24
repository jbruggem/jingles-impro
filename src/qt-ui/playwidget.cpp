
#include "playwidget.h"

#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include "QsLog.h"
#include "pushbuttonwithextras.h"

PlayWidget::PlayWidget(QWidget *parent)
	: QWidget (parent) {
	QLOG_TRACE() << "PlayWidget::PlayWidget()";

	groupBox = new QGroupBox(tr("This is the title"));
	QLOG_INFO() << "GroupBox is flat? " << (groupBox->isFlat() ? "yes" : "no");
	gridLayout   = new QGridLayout;
	layout   = new QHBoxLayout;
	playButton = new PushButtonWithExtras(tr("Play"));
	stopButton = new PushButtonWithExtras(tr("Stop"));

	layout->addWidget(playButton);
	layout->addWidget(stopButton);
	groupBox->setLayout(layout);

	gridLayout->addWidget(groupBox);

	setLayout(gridLayout);
}
