
#include "playwidget.h"

#include <QGridLayout>
#include "QsLog.h"
#include "playwidgetentry.h"

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

void PlayWidget::update(const QStringList &list) {
	clear();
	append(list);
}

void PlayWidget::append(const QStringList &list) {
	foreach(const QString &s, list) {
		entryList.append(new PlayWidgetEntry(s));
		layout->addWidget(entryList.last());
	}
}
