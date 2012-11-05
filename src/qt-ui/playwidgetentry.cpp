#include "playwidgetentry.h"

// PlayWidgetEntry::PlayWidgetEntry(const QString &title, QWidget *parent)
PlayWidgetEntry::PlayWidgetEntry(PlayWidgetEntryController * c,Track &t, QWidget *parent)
    : QWidget (parent),
      controller(c){
	QLOG_TRACE() << "PlayWidgetEntry::PlayWidgetEntry()";

    track = &t;

    controller->setTrack(track);
    controller->setParent(this);

    // debug layout
//    QPalette p(palette());
//    p.setColor(QPalette::Background, Qt::yellow);
//    setPalette(p);
//    setAutoFillBackground(true);


//    QString title = (*track->getTitle())+" ("+(*track->getArtist())+")";

    QString title = *track->getTitle();

	// groupBox = new QGroupBox(title);
    //groupBox     = new QGroupBox(QFileInfo(t.getPath()).baseName());
    //groupBox     = new QGroupBox();
    //outerLayout  = new QGridLayout;
	innerLayout  = new QGridLayout;
    buttonLayout = new QVBoxLayout;
    playButton   = new QPushButton(title);
    stopButton   = new QPushButton(tr("Stop"));

    QSizePolicy sizePol(QSizePolicy::Expanding,QSizePolicy::Expanding);
    playButton->setSizePolicy(sizePol);

	buttonLayout->addWidget(playButton);
	buttonLayout->addWidget(stopButton);
    //buttonLayout->addStretch();
	innerLayout->addLayout(buttonLayout, 0, 0);
    //groupBox->setLayout(innerLayout);
    //outerLayout->addWidget(groupBox);

    connect(playButton,SIGNAL(clicked()),controller,SLOT(playClicked()));
    connect(stopButton,SIGNAL(clicked()),controller,SLOT(stopClicked()));

    setLayout(innerLayout);
}
