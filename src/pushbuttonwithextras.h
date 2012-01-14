
#ifndef PUSHBUTTONWITHEXTRAS_H
#define PUSHBUTTONWITHEXTRAS_H

#include <QPushButton>
#include <QTimer>

class PushButtonWithExtras : public QPushButton {
	
	Q_OBJECT
	
	public:
		PushButtonWithExtras( QWidget * parent = 0 );
		PushButtonWithExtras( const QString & text, QWidget * parent = 0 );
		PushButtonWithExtras( const QIcon & icon, const QString & text, QWidget * parent = 0 );
		void setLongPressTime(int32_t msec);
	
	signals:
		void shortClicked();
		void longClicked();
	
	private slots:
		void localPressed();
		void localPressedLong();
		void localReleased();
	
	private:
		enum {
			DEFAULT_LONG_PRESS_TIME = 1000
		};
		QTimer longPressTimer;
		bool clickedFlag;
		void init();
};

#endif
