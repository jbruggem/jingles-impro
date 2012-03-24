
#include "playwidget.h"

#include <QGridLayout>
#include "QsLog.h"
#include "playwidgetentry.h"

PlayWidget::PlayWidget(QWidget *parent)
	: QWidget (parent) {
	QLOG_TRACE() << "PlayWidget::PlayWidget()";
//
	gridLayout   = new QGridLayout;
	trackEntry = new PlayWidgetEntry("track 1");
	gridLayout->addWidget(trackEntry);

	setLayout(gridLayout);
}
