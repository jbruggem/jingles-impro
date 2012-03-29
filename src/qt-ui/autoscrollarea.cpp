
#include "autoscrollarea.h"

#include <QTimer>
#include <QScrollBar>

AutoScrollArea::AutoScrollArea(QWidget *parent)
	: QScrollArea(parent) {

	// set up scrolling mode
	state = Idle;
	mode  = Continuous;
	paused = true;
	rewindAfterScroll = false;

	// set up timings
	scrollIncrement = 1;
	scrollInterval  = 10;
	waitTime        = 1000;

	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void AutoScrollArea::setMode(ScrollingMode mode) {
	this->mode = mode;
}

void AutoScrollArea::setRewindAfterScroll(bool value) {
	rewindAfterScroll = value;
}

void AutoScrollArea::setTimings(int scrollInterval, int scrollIncrement, int waitTime) {
	this->scrollInterval  = scrollInterval;
	this->scrollIncrement = scrollIncrement;
	this->waitTime        = waitTime;
}

void AutoScrollArea::stopScrolling() {
	paused = true;
	state = Idle;
	horizontalScrollBar()->setValue(horizontalScrollBar()->minimum());
}

void AutoScrollArea::pauseScrolling() {
	paused = true;
}

void AutoScrollArea::startScrolling(int delay) {
	paused = false;
	if ((state == Idle) or (state == EndOfScroll)) {
		state = ScrollMinToMax;
	}
	timer->setSingleShot(true);
	timer->start(delay);
}

void AutoScrollArea::update() {
	if (paused) {
		return;
	}
	switch(state) {
		case Idle:
			horizontalScrollBar()->setValue(horizontalScrollBar()->minimum());
			break;
		case Minimum:
			horizontalScrollBar()->setValue(horizontalScrollBar()->minimum());
			state = ScrollMinToMax;
			timer->start(waitTime);
			break;
		case ScrollMinToMax:
			if (horizontalScrollBar()->value() < horizontalScrollBar()->maximum()) {
				horizontalScrollBar()->setValue(horizontalScrollBar()->value() + scrollIncrement);
				timer->start(scrollInterval);
			} else {
				if (mode == ContinuousOneWay) {
					state = Minimum;
					timer->start(waitTime);
				} else if (mode == OneTimeOneWay) {
					state = EndOfScroll;
					timer->start();
				} else {  // Continuous or OneTime
					state = Maximum;
					timer->start(scrollInterval);
				}
			}
			break;
		case Maximum:
			state = ScrollMaxToMin;
			timer->start(waitTime);
			break;
		case ScrollMaxToMin:
			if (horizontalScrollBar()->value() > horizontalScrollBar()->minimum()) {
				horizontalScrollBar()->setValue(horizontalScrollBar()->value() - scrollIncrement);
				timer->start(scrollInterval);
			} else {
				if (mode == OneTime) {
					state = Idle;
				} else {  // Continuous
					state = Minimum;
					timer->start(scrollInterval);
				}
			}
			break;
		case EndOfScroll:
			if (rewindAfterScroll) {
				state = Idle;
				timer->start(waitTime);
			}
			break;
	}
}
