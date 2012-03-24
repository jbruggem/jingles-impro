
#include "playwidgetentry.h"

#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include "QsLog.h"
#include "pushbuttonwithextras.h"


PlayWidgetEntry::PlayWidgetEntry(const QString &title, QWidget *parent)
	: QWidget (parent) {
	QLOG_TRACE() << "PlayWidgetEntry::PlayWidgetEntry()";

	groupBox = new QGroupBox(title);
	outerLayout  = new QGridLayout;
	innerLayout  = new QGridLayout;
	buttonLayout = new QHBoxLayout;
	playButton = new PushButtonWithExtras(tr("Play"));
	stopButton = new PushButtonWithExtras(tr("Stop"));

	buttonLayout->addWidget(playButton);
	buttonLayout->addWidget(stopButton);
	innerLayout->addLayout(buttonLayout, 0, 0);
	groupBox->setLayout(innerLayout);
	outerLayout->addWidget(groupBox);

	setLayout(outerLayout);
}

void PlayWidgetEntry::setTitle (const QString &title) {
	groupBox->setTitle(title);
}
