
#include "editwidget.h"

#include <QComboBox>
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
	testModel         = new TestModel;
	stockListView     = new QTreeView;
	stockListView->setModel(testModel);
	stockListView->setHeaderHidden(true);
	stockListCBox     = new QComboBox;
	for (int i = 0; i < TestModel::NbSortingModes; i++) {
		stockListCBox->addItem(TestModel::getSortingModeText(TestModel::SortingMode(i)));
	}
	stockListGroupBox = new QGroupBox(tr("Stock List"));
	stockListGroupBox->setLayout(new QGridLayout);
	stockListGroupBox->layout()->addWidget(stockListView);
	stockListGroupBox->layout()->addWidget(stockListCBox);
	connect(stockListCBox, SIGNAL(currentIndexChanged(int)), testModel, SLOT(setSortingMode(int)));

	// set up the splitter
	splitter = new QSplitter;
	splitter->addWidget(explorerGroupBox);
	splitter->setStretchFactor(0, 1);
	splitter->addWidget(stockListGroupBox);
	splitter->setStretchFactor(1, 2);

	// set up the layout
	setLayout(new QGridLayout);
	layout()->addWidget(splitter);
}

void EditWidget::update(const TrackList *list) {
	testModel->populate(list);
}
