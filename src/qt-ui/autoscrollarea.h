
#ifndef AUTOSCROLLAREA_H_
#define AUTOSCROLLAREA_H_

#include <QScrollArea>

class QTimer;
class QScrollBar;

class AutoScrollArea : public QScrollArea {

	Q_OBJECT

	public:
		enum StateEnum {
			Minimum,
			ScrollMinToMax,
			Maximum,
			ScrollMaxToMin
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
		void setOrientation(Qt::Orientation);
	public slots:
		void startScrolling();
		void pauseScrolling();
		void stopScrolling();
		void rewind();
	private slots:
		void update();
	private:
		QTimer          *timer;
		StateEnum        state;
		ScrollingMode    mode;
		QScrollBar      *scrollBar;
		bool             paused;
		bool             rewindAfterScroll;
		int              scrollIncrement;
		int              scrollInterval;
		int              waitTime;
};

#endif
