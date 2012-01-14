
#include "pushbuttonwithextras.h"
#include <QTimer>

PushButtonWithExtras::PushButtonWithExtras( QWidget * parent ) : QPushButton (parent) {
	init();
}

PushButtonWithExtras::PushButtonWithExtras( const QString & text, QWidget * parent ) : QPushButton (text, parent) {
	init();
}

PushButtonWithExtras::PushButtonWithExtras( const QIcon & icon, const QString & text, QWidget * parent ) : QPushButton (icon, text, parent) {
	init();
}

void PushButtonWithExtras::init() {
	longPressTimer.setInterval(DEFAULT_LONG_PRESS_TIME);
	longPressTimer.setSingleShot(true);
	
	connect(this, SIGNAL(pressed()), this, SLOT(localPressed()));
	connect(this, SIGNAL(released()), this, SLOT(localReleased()));
	connect(&longPressTimer, SIGNAL(timeout()), this, SLOT(localPressedLong()));
}

void PushButtonWithExtras::setLongPressTime(int32_t msec) {
	longPressTimer.setInterval(msec);
}

void PushButtonWithExtras::localPressed() {
	// reset the flag - a button is only considered as clicked if the timer elapses or if the button is released (whichever happens first)
	clickedFlag = false;
	
	longPressTimer.start();
}

void PushButtonWithExtras::localPressedLong() {
	if (not clickedFlag) {
		emit longClicked();
		clickedFlag = true;
	}
}

void PushButtonWithExtras::localReleased() {
	longPressTimer.stop();

	if (not clickedFlag) {
		emit shortClicked();
		clickedFlag = true;
	}
}
