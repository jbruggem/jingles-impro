
#include "playwidgetentry.h"

#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDir>
#include "QsLog.h"
#include "pushbuttonwithextras.h"
#include "track.h"


// PlayWidgetEntry::PlayWidgetEntry(const QString &title, QWidget *parent)
PlayWidgetEntry::PlayWidgetEntry(const Track &t, QWidget *parent)
	: QWidget (parent) {
	QLOG_TRACE() << "PlayWidgetEntry::PlayWidgetEntry()";

	track = &t;

	// groupBox = new QGroupBox(title);
	groupBox     = new QGroupBox(QFileInfo(t.getPath()).baseName());
	outerLayout  = new QGridLayout;
	innerLayout  = new QGridLayout;
	buttonLayout = new QHBoxLayout;
	playButton   = new PushButtonWithExtras(tr("Play"));
	stopButton   = new PushButtonWithExtras(tr("Stop"));

	buttonLayout->addWidget(playButton);
	buttonLayout->addWidget(stopButton);
	buttonLayout->addStretch();
	innerLayout->addLayout(buttonLayout, 0, 0);
	groupBox->setLayout(innerLayout);
	outerLayout->addWidget(groupBox);

	setLayout(outerLayout);
}
