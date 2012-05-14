#include "playwidgetentry.h"

// PlayWidgetEntry::PlayWidgetEntry(const QString &title, QWidget *parent)
PlayWidgetEntry::PlayWidgetEntry(PlayWidgetEntryController * c,Track &t, QWidget *parent)
    : QWidget (parent),
      controller(c){
	QLOG_TRACE() << "PlayWidgetEntry::PlayWidgetEntry()";

    track = &t;

    controller->setTrack(track);
    controller->setParent(this);

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

    connect(playButton,SIGNAL(clicked()),controller,SLOT(playClicked()));
    connect(stopButton,SIGNAL(clicked()),controller,SLOT(stopClicked()));

	setLayout(outerLayout);
}
