
#include "editwidget.h"

#include <QGridLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>
#include "QsLog.h"

EditWidget::EditWidget(QWidget *parent)
	: QWidget(parent) {

	layout = new QGridLayout;

	dirsOnlyModel = new QFileSystemModel;
	dirsOnlyModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dirsOnlyModel->setRootPath(QDir::rootPath());
	leftPane = new QTreeView;
	leftPane->setModel(dirsOnlyModel);
	// only show first column (folder names)
	for (int i = 1; i < dirsOnlyModel->columnCount(); i++) {
		leftPane->hideColumn(i);
	}
	// hide the column headers
	leftPane->setHeaderHidden(true);
	// expand the first element, otherwise the tree is fully collapsed
	leftPane->expandToDepth(0);
	// select the first element
	leftPane->setCurrentIndex(dirsOnlyModel->index(dirsOnlyModel->rootPath()));

	fileModel = new QFileSystemModel;
	fileModel->setRootPath(QDir::rootPath());
	rightPane = new QTreeView;
	rightPane->setModel(fileModel);
	rightPane->setSelectionMode(QAbstractItemView::ExtendedSelection);
	rightPaneUpdate(fileModel->index(fileModel->rootPath()));

	layout->addWidget(leftPane, 0, 0);
	layout->addWidget(rightPane, 0, 1);
	setLayout(layout);

	connect(leftPane->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(rightPaneUpdate(const QModelIndex &)));
	connect(rightPane, SIGNAL(activated(const QModelIndex &)), this, SLOT(rightPaneUpdate(const QModelIndex &)));
	connect(fileModel, SIGNAL(directoryLoaded(const QString &)), this, SLOT(rightPaneSelectFirstRow()));
}

void EditWidget::rightPaneUpdate(const QModelIndex &index) {
	QLOG_TRACE() << "EditWidget::rightPaneUpdate()";
	// make sure that all folders are collapsed whenever the selection changes
	rightPane->collapseAll();
	rightPane->setRootIndex(fileModel->setRootPath(dirsOnlyModel->fileInfo(index).absoluteFilePath()));
}

void EditWidget::rightPaneSelectFirstRow() {
	QLOG_TRACE() << "EditWidget::rightPaneSelectFirstRow()";
	fileModel->sort(0, Qt::AscendingOrder);
	QLOG_TRACE() << fileModel->index(0, 0, rightPane->rootIndex()).data();
	QLOG_TRACE() << rightPane->rootIndex().child(0, 0).data() << rightPane->rootIndex().child(0, 0).isValid();

	if (rightPane->rootIndex().child(0, 0).isValid()) {
		rightPane->setCurrentIndex(rightPane->rootIndex().child(0, 0));
	}
}
