
#ifndef PLAYWIDGET_H_
#define PLAYWIDGET_H_

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QPushButton>
#include "uicontroller.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include "QsLog.h"
#include "playwidgetentry.h"
#include "tracklist.h"
#include "tracklistmodel.h"

// See http://www.qtcentre.org/archive/index.php/t-28905.html
// qstyleoption.h uses "None" and QListView includes it, so we undef None
// just before the include.
#ifdef None
#undef None
#endif
#include <QListView>

class PlayWidget : public QWidget {

	Q_OBJECT

	public:
        PlayWidget(UiController *, int, QWidget *parent = 0);
		void clear();
        void update(const TrackList *buttons, TrackList * list);
        QString prettyTime(long duration);

    public slots:
        void updatePlayerPosition(long position);
	private:
        void append(const TrackList *);
		int rowSize;
		int currentRow;
		int currentColumn;
        TrackList * tracklist;
        QList<QString> shortcutKeys;
		QGridLayout *layout;
        QGridLayout *wrapperLayout;
        QListView * playListWidget;
        QLabel * currentPlayingTime;
        QPushButton * pauseButton;
        QAbstractListModel * playListWidgetModel;
		QList<PlayWidgetEntry *> entryList;
        UiController * controller;

        QString const * getKey(int i);

        QString static noKey;
};

#endif
