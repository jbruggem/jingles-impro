
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

	// connect(fsModel, SIGNAL(directoryLoaded(const QString &)), this, SLOT(doSth()));
	connect(leftPane->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(leftPaneSelectionChanged(const QModelIndex &)));

	fileModel = new QFileSystemModel;
	fileModel->setRootPath(QDir::rootPath());
	rightPane = new QTreeView;
	rightPane->setModel(fileModel);
	rightPane->setSelectionMode(QAbstractItemView::ExtendedSelection);

	layout->addWidget(leftPane, 0, 0);
	layout->addWidget(rightPane, 0, 1);
	setLayout(layout);
}

void EditWidget::leftPaneSelectionChanged(const QModelIndex &current) {
	QLOG_TRACE() << "EditWidget::leftPaneSelectionChanged()";
	QLOG_INFO()  << "selection:" << dirsOnlyModel->fileInfo(current).absoluteFilePath();
	rightPane->setRootIndex(fileModel->setRootPath(dirsOnlyModel->fileInfo(current).absoluteFilePath()));
}
