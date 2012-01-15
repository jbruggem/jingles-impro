
#include "improgui.h"

#include <QHBoxLayout>
#include <QSignalMapper>
#include <QFileDialog>
#include "QsLog.h"
#include "pushbuttonwithextras.h"
#include "tracklisthandler.h"

ImproGui::ImproGui() {
	centralWidget = new QWidget;
	setCentralWidget(centralWidget);

	button = new PushButtonWithExtras("...");

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(button);
	centralWidget->setLayout(layout);

	QSignalMapper *shortClickMapper = new QSignalMapper(this);
	QSignalMapper *longClickMapper  = new QSignalMapper(this);
	shortClickMapper->setMapping(button, 0);
	longClickMapper->setMapping(button, 0);

	connect(button, SIGNAL(shortClicked()), shortClickMapper, SLOT(map()));
	connect(button, SIGNAL(longClicked()),  longClickMapper,  SLOT(map()));

	connect(shortClickMapper, SIGNAL(mapped(int)), this, SLOT(buttonShortClicked(int)));
	connect(longClickMapper,  SIGNAL(mapped(int)), this, SLOT(buttonLongClicked(int)));
}

void ImproGui::linkTo(TrackListHandler *tlh) {
	this->tlh = tlh;
}

bool ImproGui::addTrackWithDialog() {
	QString path = QFileDialog::getOpenFileName(this);
	if (path.isEmpty()) {
		return false;
	}
	tlh->add(path);
	tlh->print();
	return true;
}

bool ImproGui::setTrackPathWithDialog(int32_t index) {
	QString path = QFileDialog::getOpenFileName(this);
	if (path.isEmpty()) {
		return false;
	}
	tlh->setPath(index, path);
	tlh->print();
	return true;
}

void ImproGui::buttonShortClicked(int buttonNumber) {
	QLOG_TRACE() << "Button" << buttonNumber << "short clicked.";
	if (not tlh->exists(buttonNumber)) {
		if (addTrackWithDialog()) {
			button->setText(QFileInfo(tlh->getPath(buttonNumber)).baseName());
		}
	} else {
		if (tlh->isPlaying(buttonNumber)) {
			tlh->stop(buttonNumber);
		} else {
			tlh->play(buttonNumber);
		}
	}
}

void ImproGui::buttonLongClicked(int buttonNumber) {
	QLOG_TRACE() << "Button" << buttonNumber << "long clicked.";
	if (not tlh->exists(buttonNumber)) {
		if (addTrackWithDialog()) {
			button->setText(QFileInfo(tlh->getPath(buttonNumber)).baseName());
		}
	} else {
		setTrackPathWithDialog(buttonNumber);
		button->setText(QFileInfo(tlh->getPath(buttonNumber)).baseName());
	}
}
