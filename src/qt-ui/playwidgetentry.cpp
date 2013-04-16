#include "playwidgetentry.h"
// PlayWidgetEntry::PlayWidgetEntry(const QString &title, QWidget *parent)
PlayWidgetEntry::PlayWidgetEntry(PlayWidgetEntryController * c,Track &t, QWidget *parent, QString const & shortcutKey)
    : QWidget (parent),
      controller(c),
      shortcutKey(shortcutKey){
	QLOG_TRACE() << "PlayWidgetEntry::PlayWidgetEntry()";

    track = &t;

    controller->setTrack(track);
    controller->setParent(this);

    build();

    connect(controller,SIGNAL(stateChanged(bool)),this,SLOT(stateChanged(bool)));
    connect(controller,SIGNAL(trackInfosUpdated()),this,SLOT(trackInfosUpdated()));

    connect(playButton,SIGNAL(clicked()),controller,SLOT(playClicked()));
    connect(stopButton,SIGNAL(clicked()),controller,SLOT(stopClicked()));

    if(shortcutKey.length()){
        shortcutPlay = new QShortcut(QKeySequence(shortcutKey), this);
        shortcutStop = new QShortcut("Ctrl+"+shortcutKey, this);
        connect(shortcutPlay,SIGNAL(activated()),controller,SLOT(playClicked()));
        connect(shortcutStop,SIGNAL(activated()),controller,SLOT(stopClicked()));
        QLOG_TRACE() << "PlayWidgetEntry: set shortcut key to "<< shortcutKey;
    }else{
        QLOG_TRACE() << "PlayWidgetEntry: no shortcut key.";
    }
}

void PlayWidgetEntry::build(){
    QLOG_TRACE() << "PlayWidgetEntry::build()";
    innerLayout  = new QGridLayout;
    buttonLayout = new QVBoxLayout;
    playButton   = new QPushButton("loading...");
    stopButton   = new QPushButton(tr("Stop"));

    QSizePolicy sizePol(QSizePolicy::Expanding,QSizePolicy::Expanding);
    playButton->setSizePolicy(sizePol);

    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(stopButton);
    innerLayout->addLayout(buttonLayout, 0, 0);
    setLayout(innerLayout);

    updateTags();
}

void PlayWidgetEntry::updateTags(){
    QLOG_TRACE() << "PlayWidgetEntry::updateTags " << shortcutKey;
    playButton->setText(
                (shortcutKey.length()?"["+shortcutKey+"] ":"")
        + track->getDisplayName()
    );
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
    //QLOG_TRACE() << "PlayWidgetEntry::trackInfosUpdated()" << shortcutKey;
    this->updateTags();
}
