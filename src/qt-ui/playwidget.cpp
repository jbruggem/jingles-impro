
#include "playwidget.h"

PlayWidget::PlayWidget(UiController * controller, int rowSize, QWidget *parent)
	: QWidget (parent),
	  rowSize (rowSize),
	  currentRow (0),
      currentColumn (0),
      controller(controller){
	QLOG_TRACE() << "PlayWidget::PlayWidget()";

    shortcutKeys.append("a");
    shortcutKeys.append("z");
    shortcutKeys.append("e");
    shortcutKeys.append("q");
    shortcutKeys.append("s");
    shortcutKeys.append("d");
    shortcutKeys.append("w");
    shortcutKeys.append("x");
    shortcutKeys.append("c");

    // debug layout
//    QPalette p(palette());
//    p.setColor(QPalette::Background, Qt::blue);
//    setPalette(p);
//    setAutoFillBackground(true);


    wrapperLayout = new QGridLayout(this);
    
    layout = new QGridLayout(this);
    wrapperLayout->addLayout(layout, 1,1);
    
    playListWidget = new QListView(this);
    currentPlayingTime = new QLabel("",this);
    currentPlayingTime->setAlignment(Qt::AlignHCenter);
    pauseButton = new QPushButton("play/pause",this);


    QHBoxLayout * playlistControlLayout = new QHBoxLayout(this);
    playlistControlLayout->addWidget(pauseButton);
    playlistControlLayout->addWidget(currentPlayingTime);

    QVBoxLayout * playlistLayout = new QVBoxLayout(this);
    playlistLayout->addWidget(playListWidget);
    playlistLayout->addLayout(playlistControlLayout);

    // initialize the animation
    anim_init();
    wrapperLayout->addWidget(anim_button, 0,1);
    wrapperLayout->addWidget(anim_label, 1,0);

    //connect(playListWidget,SIGNAL(clicked(QModelIndex)),controller,SLOT(playFromPlaylist(QModelIndex)));
    connect(playListWidget,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(playFromPlaylist(QModelIndex)));
    connect(pauseButton,SIGNAL(clicked()),controller,SLOT(pausePlaylist()));
    connect(controller,SIGNAL(updatePlayerPosition(long)),this,SLOT(updatePlayerPosition(long)));

    wrapperLayout->addLayout(playlistLayout, 1,2);


    //QVBoxLayout *layoutWithStretch = new QVBoxLayout;
    //layoutWithStretch->addLayout(layout);
    //layoutWithStretch->addStretch();

    setLayout(wrapperLayout);
}

void PlayWidget::updatePlayerPosition(long position){
    currentPlayingTime->setText(prettyTime(position)+" / "+prettyTime(controller->currentPlayerEndingTime()));
}

QString PlayWidget::prettyTime(long duration){
    int min = duration/1000/60;
    int sec = duration/1000- min*60;
    return (min<10?"0":"")+QString::number(min)+":"+(sec<10?"0":"")+QString::number(sec);
}

void PlayWidget::clear() {
	qDeleteAll(entryList);
	entryList.clear();
	currentRow    = 0;
	currentColumn = 0;
}

void PlayWidget::update(const TrackList *buttons, TrackList * list) {
	clear();
    append(buttons);

    tracklist = list;

    playListWidgetModel = new TrackListModel(tracklist,this);
    playListWidget->setModel(playListWidgetModel);

    for(int i=0; i< tracklist->length(); i++)
        controller->load(tracklist->at(i));
}
QString PlayWidget::noKey = QString("");

QString const * PlayWidget::getKey(int i){
    if(i >= shortcutKeys.length())
        return &PlayWidget::noKey;
    return &shortcutKeys[i];
}

void PlayWidget::append(const TrackList *buttons) {
    for(int i = 0; i < buttons->size(); i++) {
        entryList.append(new PlayWidgetEntry(controller->getPlayWidgetEntryController(),*buttons->at(i),this,*getKey(i)));
		layout->addWidget(entryList.last(), currentRow, currentColumn);

		currentColumn = (currentColumn + 1) % rowSize;
		if (not currentColumn) {
			currentRow++;
		}
	}
}

void PlayWidget::anim_init() {
    anim_label = new QLabel("This is a test label for the animation");
    anim_state = LABEL_HIDDEN;
    anim_label->setMaximumWidth(0);
    
    // setup animations
    anim_labelWidth = new QPropertyAnimation(anim_label, "maximumWidth");
    anim_labelWidth->setDuration(500);
    anim_labelWidth->setStartValue(0);
    // end value to be defined when starting the transition
    anim_labelWidth->setEasingCurve(QEasingCurve::InOutQuad);
    
    anim_listWidth = new QPropertyAnimation(playListWidget, "maximumWidth");
    anim_listWidth->setDuration(500);
    // start value to be defined when starting the transition
    anim_listWidth->setEndValue(0);
    anim_listWidth->setEasingCurve(QEasingCurve::InOutQuad);
    
    anim_transition = new QParallelAnimationGroup;
    anim_transition->addAnimation(anim_labelWidth);
    anim_transition->addAnimation(anim_listWidth);
    
    anim_button = new QPushButton("animate");
    
    connect(anim_button,     SIGNAL(clicked()),  this, SLOT(anim_buttonPressed()));
    connect(anim_transition, SIGNAL(finished()), this, SLOT(anim_transitionFinished()));
}


void PlayWidget::anim_buttonPressed() {
    QLOG_TRACE() << "PlayWidget::anim_buttonPressed()";
    
    if (anim_state == LABEL_HIDDEN) {
        anim_labelWidth->setEndValue(playListWidget->width());
        anim_listWidth->setStartValue(playListWidget->width());
        anim_button->setEnabled(false);
        anim_transition->setDirection(QAbstractAnimation::Forward);
        anim_transition->start();
        
    } else if (anim_state == LABEL_SHOWN) {
        anim_labelWidth->setEndValue(anim_label->width());
        anim_listWidth->setStartValue(anim_label->width());
        anim_button->setEnabled(false);
        anim_transition->setDirection(QAbstractAnimation::Backward);
        anim_transition->start();
    }
}

void PlayWidget::anim_transitionFinished() {
    QLOG_TRACE() << "PlayWidget::anim_transitionFinished()";
    
    if (anim_state == LABEL_HIDDEN) {
        anim_state = LABEL_SHOWN;
        anim_label->setMaximumWidth(QWIDGETSIZE_MAX);
    } else if (anim_state == LABEL_SHOWN) {
        anim_state = LABEL_HIDDEN;
        playListWidget->setMaximumWidth(QWIDGETSIZE_MAX);
    }
    anim_button->setEnabled(true);
}

