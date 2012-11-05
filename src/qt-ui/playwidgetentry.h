
#ifndef PLAYWIDGETENTRY_H_
#define PLAYWIDGETENTRY_H_

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QPushButton>
#include "QsLog.h"
#include "track.h"
#include "playwidgetentrycontroller.h"

class PlayWidgetEntry : public QWidget {

	Q_OBJECT

	public:
		// PlayWidgetEntry(const QString &, QWidget * = 0);
        PlayWidgetEntry(PlayWidgetEntryController * c,Track &, QWidget * = 0);
	private:
		QGroupBox   *groupBox;
		QGridLayout *outerLayout;
		QGridLayout *innerLayout;
        QVBoxLayout *buttonLayout;
        QPushButton *playButton;
        QPushButton *stopButton;
        Track *track;
        PlayWidgetEntryController * controller;
};

#endif
