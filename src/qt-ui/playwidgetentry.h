
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

class PlayWidgetEntry : public QWidget {

	Q_OBJECT

	public:
		// PlayWidgetEntry(const QString &, QWidget * = 0);
		PlayWidgetEntry(const Track &, QWidget * = 0);
	private:
		QGroupBox   *groupBox;
		QGridLayout *outerLayout;
		QGridLayout *innerLayout;
		QHBoxLayout *buttonLayout;
        QPushButton *playButton;
        QPushButton *stopButton;
		const Track *track;
};

#endif
