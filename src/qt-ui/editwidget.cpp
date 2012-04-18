
#include "editwidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "twopaneexplorer.h"

EditWidget::EditWidget(QWidget *parent)
	: QWidget(parent) {

	explorerLabel = new QLabel(tr("FileExplorer"));
	explorer = new TwoPaneExplorer;
	QVBoxLayout *explorerLayout = new QVBoxLayout;
	explorerLayout->addWidget(explorerLabel);
	explorerLayout->addWidget(explorer);

	stockListLabel = new QLabel(tr("Stock List"));
	stockListView = new QListWidget;
	QVBoxLayout *stockListLayout = new QVBoxLayout;
	stockListLayout->addWidget(stockListLabel);
	stockListLayout->addSpacing(9);
	stockListLayout->addWidget(stockListView);
	stockListLayout->addSpacing(9);

	layout   = new QGridLayout;
	layout->addLayout(explorerLayout, 0, 0);
	layout->setColumnStretch(0, 2);
	layout->addLayout(stockListLayout, 0, 1);
	layout->setColumnStretch(1, 1);
	setLayout(layout);
}
