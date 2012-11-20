
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


    wrapperLayout = new QHBoxLayout(this);
    layout = new QGridLayout(this);
    wrapperLayout->addLayout(layout, 0);

    playListWidget = new QListView(this);
    QVBoxLayout * playlistLayout = new QVBoxLayout(this);
    playlistLayout->addWidget(playListWidget);


    wrapperLayout->addLayout(playlistLayout, 0);

    //QVBoxLayout *layoutWithStretch = new QVBoxLayout;
    //layoutWithStretch->addLayout(layout);
    //layoutWithStretch->addStretch();

    setLayout(wrapperLayout);
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
    playListWidget->setModel(tracklist);
}

QString const * PlayWidget::getKey(int i){
    if(i >= shortcutKeys.length())
        return NULL;
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
