
#ifndef PLAYWIDGET_H_
#define PLAYWIDGET_H_

#include <QWidget>
#include <QList>

class QGridLayout;
class PlayWidgetEntry;
class TrackList;

class PlayWidget : public QWidget {

	Q_OBJECT

	public:
		PlayWidget(int, QWidget *parent = 0);
		void clear();
		// void update(const QStringList &);
		// void append(const QStringList &);
		void update(const TrackList &);
		void append(const TrackList &);
	private:
		int rowSize;
		int currentRow;
		int currentColumn;
		QGridLayout *layout;
		QList<PlayWidgetEntry *> entryList;
};

#endif
