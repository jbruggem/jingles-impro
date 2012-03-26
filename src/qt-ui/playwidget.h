
#ifndef PLAYWIDGET_H_
#define PLAYWIDGET_H_

#include <QWidget>
#include <QList>

class QGridLayout;
class PlayWidgetEntry;

class PlayWidget : public QWidget {

	Q_OBJECT

	public:
		PlayWidget(QWidget *parent = 0);
		void clear();
		void update(const QStringList &);
		void append(const QStringList &);
	private:
		QGridLayout *layout;
		QList<PlayWidgetEntry *> entryList;
};

#endif
