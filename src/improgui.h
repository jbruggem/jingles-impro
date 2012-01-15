
#ifndef IMPROGUI_H_
#define IMPROGUI_H_

#include <QMainWindow>
#include <stdint.h>
#include "tracklisthandler.h"

class QMainWindow;
class PushButtonWithExtras;

class ImproGui : public QMainWindow {
	
	Q_OBJECT
	
	public:
		ImproGui();
		void linkTo(TrackListHandler *);
	private slots:
		void buttonShortClicked(int);
		void buttonLongClicked(int);
	private:
		bool addTrackWithDialog();
		bool setTrackPathWithDialog(int32_t);
		QWidget *centralWidget;
		PushButtonWithExtras *button;
		TrackListHandler *tlh;
};

#endif
