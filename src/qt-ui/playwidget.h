
#ifndef PLAYWIDGET_H_
#define PLAYWIDGET_H_

#include <QWidget>
#include <QList>
#include "uicontroller.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include "QsLog.h"
#include "playwidgetentry.h"
#include "tracklist.h"

class PlayWidget : public QWidget {

	Q_OBJECT

	public:
        PlayWidget(UiController *, int, QWidget *parent = 0);
		void clear();
		void update(const TrackList *);
		void append(const TrackList *);
	private:
		int rowSize;
		int currentRow;
		int currentColumn;
		QGridLayout *layout;
		QList<PlayWidgetEntry *> entryList;
        UiController * controller;
};

#endif
