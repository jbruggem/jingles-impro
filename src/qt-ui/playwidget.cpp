
#include "playwidget.h"

#include <QGridLayout>
#include "QsLog.h"
#include "playwidgetentry.h"
#include "tracklist.h"

PlayWidget::PlayWidget(QWidget *parent)
	: QWidget (parent) {
	QLOG_TRACE() << "PlayWidget::PlayWidget()";

	layout    = new QGridLayout;
	setLayout(layout);
}

void PlayWidget::clear() {
	qDeleteAll(entryList);
	entryList.clear();
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
		layout->addWidget(entryList.last());
	}
}
