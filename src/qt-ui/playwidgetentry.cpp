#include "playwidgetentry.h"

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
    playButton   = new QPushButton(tr("Play"));
    stopButton   = new QPushButton(tr("Stop"));

	buttonLayout->addWidget(playButton);
	buttonLayout->addWidget(stopButton);
	buttonLayout->addStretch();
	innerLayout->addLayout(buttonLayout, 0, 0);
	groupBox->setLayout(innerLayout);
	outerLayout->addWidget(groupBox);

	setLayout(outerLayout);
}
