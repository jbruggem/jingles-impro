
#include "playwidget.h"

#include <QGridLayout>
#include "QsLog.h"
#include "playwidgetentry.h"
#include "tracklist.h"

PlayWidget::PlayWidget(int rowSize, QWidget *parent)
	: QWidget (parent),
	  rowSize (rowSize),
	  currentRow (0),
	  currentColumn (0) {
	QLOG_TRACE() << "PlayWidget::PlayWidget()";

	layout    = new QGridLayout;
	setLayout(layout);
}

void PlayWidget::clear() {
	qDeleteAll(entryList);
	entryList.clear();
	currentRow    = 0;
	currentColumn = 0;
}

// void PlayWidget::update(const QStringList &list) {
void PlayWidget::update(const TrackList &list) {
	clear();
	append(list);
}

// void PlayWidget::append(const QStringList &list) {
void PlayWidget::append(const TrackList &list) {
	for(int i = 0; i < list.size(); i++) {
		entryList.append(new PlayWidgetEntry(*list.at(i)));
		layout->addWidget(entryList.last(), currentRow, currentColumn);

		currentColumn = (currentColumn + 1) % rowSize;
		if (not currentColumn) {
			currentRow++;
		}
	}
}
