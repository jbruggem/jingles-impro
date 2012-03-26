
#ifndef PLAYWIDGETENTRY_H_
#define PLAYWIDGETENTRY_H_

#include <QWidget>

class QGroupBox;
class QGridLayout;
class QHBoxLayout;
class PushButtonWithExtras;
class Track;

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
		PushButtonWithExtras *playButton;
		PushButtonWithExtras *stopButton;
		const Track *track;
};

#endif
