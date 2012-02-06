
#include "buttonpanel.h"

#include "pushbuttonwithextras.h"
#include <QStringList>
#include <QHBoxLayout>
#include <QSignalMapper>
#include "QsLog.h"

ButtonPanel::ButtonPanel() {
	init();
}

ButtonPanel::ButtonPanel(const QStringList &labels) {
	init();
	addButtons(labels);
}

void ButtonPanel::init() {
	layout = new QHBoxLayout;
	setLayout(layout);
	
	shortClickMapper = new QSignalMapper(this);
	longClickMapper  = new QSignalMapper(this);

	connect(shortClickMapper, SIGNAL(mapped(int)), this, SLOT(buttonShortClickedSlot(int)));
	connect(shortClickMapper, SIGNAL(mapped(int)), this, SIGNAL(buttonShortClicked(int)));
	connect(longClickMapper,  SIGNAL(mapped(int)), this, SLOT(buttonLongClickedSlot(int)));
	connect(longClickMapper,  SIGNAL(mapped(int)), this, SIGNAL(buttonLongClicked(int)));
}

void ButtonPanel::addButton(const QString &label) {
	// Create the new button
	PushButtonWithExtras *b = new PushButtonWithExtras(label);
	
	// Map button signals to this class' slots
	connect(b, SIGNAL(shortClicked()), shortClickMapper, SLOT(map()));
	connect(b, SIGNAL(longClicked()),  longClickMapper,  SLOT(map()));
	shortClickMapper->setMapping(b, buttonList.length());
	longClickMapper->setMapping(b, buttonList.length());
	
	// Add the button to the list and to the layout
	buttonList.append(b);
	layout->addWidget(b);
}

void ButtonPanel::addButtons(const QStringList &labels) {
	foreach(const QString &l, labels) {
		addButton(l);
	}
}

void ButtonPanel::clear() {
	qDeleteAll(buttonList);
	buttonList.clear();
}
