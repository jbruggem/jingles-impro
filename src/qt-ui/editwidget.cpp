
#include "editwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QSplitter>
#include <QTreeView>
#include "testmodel.h"
#include "tracklist.h"
#include "twopaneexplorer.h"

EditWidget::EditWidget(QWidget *parent)
	: QWidget(parent) {

	// set up the file explorer
	explorer         = new TwoPaneExplorer;
	explorerGroupBox = new QGroupBox(tr("FileExplorer"));
	explorerGroupBox->setLayout(new QGridLayout);
	explorerGroupBox->layout()->addWidget(explorer);

	// set up the StockList
	stockListView     = new QTreeView;
	stockListGroupBox = new QGroupBox(tr("Stock List"));
	stockListGroupBox->setLayout(new QGridLayout);
	stockListGroupBox->layout()->addWidget(stockListView);
	testModel = new TestModel;
	stockListView->setModel(testModel);
	stockListView->setHeaderHidden(true);

	// set up the splitter
	splitter = new QSplitter;
	splitter->addWidget(explorerGroupBox);
	splitter->setStretchFactor(0, 2);
	splitter->addWidget(stockListGroupBox);
	splitter->setStretchFactor(1, 1);

	// set up the layout
	setLayout(new QGridLayout);
	layout()->addWidget(splitter);
}

void EditWidget::update(const TrackList *list) {
	testModel->populate(list);
}
