
#include "playwidget.h"



PlayWidget::PlayWidget(UiController * controller, int rowSize, QWidget *parent)
	: QWidget (parent),
	  rowSize (rowSize),
	  currentRow (0),
      currentColumn (0),
      controller(controller){
	QLOG_TRACE() << "PlayWidget::PlayWidget()";

    // debug layout
//    QPalette p(palette());
//    p.setColor(QPalette::Background, Qt::blue);
//    setPalette(p);
//    setAutoFillBackground(true);


	layout    = new QGridLayout;
    //QVBoxLayout *layoutWithStretch = new QVBoxLayout;
    //layoutWithStretch->addLayout(layout);
    //layoutWithStretch->addStretch();
    setLayout(layout);
}

void PlayWidget::clear() {
	qDeleteAll(entryList);
	entryList.clear();
	currentRow    = 0;
	currentColumn = 0;
}

void PlayWidget::update(const TrackList *list) {
	clear();
	append(list);
}

void PlayWidget::append(const TrackList *list) {
	for(int i = 0; i < list->size(); i++) {
        entryList.append(new PlayWidgetEntry(controller->getPlayWidgetEntryController(),*list->at(i)));
		layout->addWidget(entryList.last(), currentRow, currentColumn);

		currentColumn = (currentColumn + 1) % rowSize;
		if (not currentColumn) {
			currentRow++;
		}
	}
}
