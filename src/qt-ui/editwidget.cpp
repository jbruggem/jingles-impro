
#include "editwidget.h"

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QTreeView>
#include "tracklisttreemodel.h"
#include "tracklist.h"
#include "twopaneexplorer.h"

EditWidget::EditWidget(QWidget *parent)
	: QWidget(parent) {

	// set up the file explorer
	explorer         = new TwoPaneExplorer;
	addButton        = new QPushButton("-->");
	explorerGroupBox = new QGroupBox(tr("FileExplorer"));
	explorerGroupBox->setLayout(new QHBoxLayout);
	explorerGroupBox->layout()->addWidget(explorer);
	explorerGroupBox->layout()->addWidget(addButton);

	// set up the StockList
	trackListModel = new TrackListTreeModel;
	stockListView  = new QTreeView;
	stockListView->setModel(trackListModel);
	stockListView->setHeaderHidden(true);
	stockListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	stockListCBox     = new QComboBox;
	for (int i = 0; i < TrackListTreeModel::NbSortingModes; i++) {
		stockListCBox->addItem(TrackListTreeModel::getSortingModeText(TrackListTreeModel::SortingMode(i)));
	}
	stockListGroupBox = new QGroupBox(tr("Stock List"));
	stockListGroupBox->setLayout(new QGridLayout);
	stockListGroupBox->layout()->addWidget(stockListView);
	stockListGroupBox->layout()->addWidget(stockListCBox);

	// set up the splitter
	splitter = new QSplitter;
	splitter->addWidget(explorerGroupBox);
	splitter->setStretchFactor(0, 1);
	splitter->addWidget(stockListGroupBox);
	splitter->setStretchFactor(1, 2);

	// set up the layout
	setLayout(new QGridLayout);
	layout()->addWidget(splitter);

	// connect signals and slots
	connect(stockListCBox, SIGNAL(currentIndexChanged(int)), trackListModel, SLOT(setSortingMode(int)));
	connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
}

void EditWidget::update(const TrackList *list) {
	trackListModel->populate(list);
}

void EditWidget::addButtonClicked() {
	QLOG_TRACE() << "EditWidget::addButtonClicked()";
	trackListModel->addTracks(explorer->getSelection());
}
