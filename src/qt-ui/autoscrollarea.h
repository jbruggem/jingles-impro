
#ifndef AUTOSCROLLAREA_H_
#define AUTOSCROLLAREA_H_

#include <QScrollArea>

class QTimer;

class AutoScrollArea : public QScrollArea {

	Q_OBJECT

	public:
		enum StateEnum {
			Idle,
			Minimum,
			ScrollMinToMax,
			Maximum,
			ScrollMaxToMin,
			EndOfScroll
		};
		enum ScrollingMode {
			Continuous,
			ContinuousOneWay,
			OneTime,
			OneTimeOneWay
		};
		AutoScrollArea(QWidget *parent = 0);
		void setMode(ScrollingMode);
		void setRewindAfterScroll(bool);
		void setTimings(int scrollInterval, int scrollIncrement, int waitTime);
		void startScrolling(int delay = 0);
		void stopScrolling();
		void pauseScrolling();
	private slots:
		void update();
	private:
		QTimer       *timer;
		StateEnum     state;
		ScrollingMode mode;
		bool          paused;
		bool          rewindAfterScroll;
		int           scrollIncrement;
		int           scrollInterval;
		int           waitTime;
};

#endif
