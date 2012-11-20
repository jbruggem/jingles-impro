#include "playwidgetentry.h"

// PlayWidgetEntry::PlayWidgetEntry(const QString &title, QWidget *parent)
PlayWidgetEntry::PlayWidgetEntry(PlayWidgetEntryController * c,Track &t, QWidget *parent)
    : QWidget (parent),
      controller(c){
	QLOG_TRACE() << "PlayWidgetEntry::PlayWidgetEntry()";

    track = &t;

    controller->setTrack(track);
    controller->setParent(this);

    build();

    connect(controller,SIGNAL(stateChanged(bool)),this,SLOT(stateChanged(bool)));
    connect(controller,SIGNAL(trackInfosUpdated()),this,SLOT(trackInfosUpdated()));

    connect(playButton,SIGNAL(clicked()),controller,SLOT(playClicked()));
    connect(stopButton,SIGNAL(clicked()),controller,SLOT(stopClicked()));

}

void PlayWidgetEntry::build(){
    QLOG_TRACE() << "PlayWidgetEntry::build()";
    innerLayout  = new QGridLayout;
    buttonLayout = new QVBoxLayout;
    playButton   = new QPushButton(track->getFilename());
    stopButton   = new QPushButton(tr("Stop"));

    QSizePolicy sizePol(QSizePolicy::Expanding,QSizePolicy::Expanding);
    playButton->setSizePolicy(sizePol);

    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(stopButton);
    innerLayout->addLayout(buttonLayout, 0, 0);
    setLayout(innerLayout);
}

void PlayWidgetEntry::updateTags(){
    //QLOG_TRACE() << "PlayWid(getEntry::update()";
    QString text;
    if(track->getTitle()->length() > 0 && !track->shouldShowFilename()){
        text = (*track->getTitle());
    }else{
        text = track->getFilename();
    }
    playButton->setText(text);
}


void PlayWidgetEntry::stateChanged(bool isNowPlaying){
    QFont font = QFont(playButton->font());
    if(isNowPlaying){
        font.setBold(true);
    }else{
        font.setBold(false);
    }
    playButton->setFont(font);
}

void PlayWidgetEntry::trackInfosUpdated(){
    //QLOG_TRACE() << "PlayWidgetEntry::trackInfosUpdated()";
    this->updateTags();
}
