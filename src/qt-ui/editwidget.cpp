
#include "editwidget.h"

#include <QGridLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>
#include <QTimer>
#include "QsLog.h"

EditWidget::EditWidget(QWidget *parent)
	: QWidget(parent) {

	// set up the left pane
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

	// set up the right pane
	fileModel = new QFileSystemModel;
	fileModel->setRootPath(QDir::rootPath());
	rightPane = new QTreeView;
	rightPane->setModel(fileModel);
	rightPane->setSelectionMode(QAbstractItemView::ExtendedSelection);
	rightPaneUpdate(fileModel->rootPath());

	// set up the layout
	layout = new QGridLayout;
	layout->addWidget(leftPane, 0, 0);
	layout->addWidget(rightPane, 0, 1);
	setLayout(layout);

	// connect signals to slots
	connect(leftPane->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(leftPaneItemSelected(const QModelIndex &)));
	connect(rightPane, SIGNAL(activated(const QModelIndex &)), this, SLOT(rightPaneItemActivated(const QModelIndex &)));
	connect(fileModel, SIGNAL(directoryLoaded(const QString &)), this, SLOT(rightPaneSelectFirstRow()));
}

void EditWidget::leftPaneItemSelected(const QModelIndex &index) {
	QLOG_TRACE() << "EditWidget::leftPaneItemSelected()";
	QString openDir(reinterpret_cast<const QFileSystemModel *>(index.model())->fileInfo(index).absoluteFilePath());
	QLOG_TRACE() << "directory:" << openDir;
	rightPaneUpdate(openDir);
}

void EditWidget::rightPaneItemActivated(const QModelIndex &index) {
	QLOG_TRACE() << "EditWidget::rightPaneItemActivated()";
	QString openDir(reinterpret_cast<const QFileSystemModel *>(index.model())->fileInfo(index).absoluteFilePath());
	QLOG_TRACE() << "directory:" << openDir;
	rightPaneUpdate(openDir);
	leftPaneUpdate(openDir);
}

void EditWidget::leftPaneUpdate(const QString &dir) {
	QLOG_TRACE() << "EditWidget::leftPaneUpdate()";

	leftPane->setCurrentIndex(dirsOnlyModel->index(dir));
}

void EditWidget::rightPaneUpdate(const QString &dir) {
	QLOG_TRACE() << "EditWidget::rightPaneUpdate()";
	// make sure that all folders are collapsed whenever the selection changes
	rightPane->collapseAll();
	rightPane->setRootIndex(fileModel->setRootPath(dir));
}

void EditWidget::rightPaneSelectFirstRow() {
	QLOG_TRACE() << "EditWidget::rightPaneSelectFirstRow()";

	// the model is not sorted by default, meaning the first child is not the first entry in the view.
	fileModel->sort(0, Qt::AscendingOrder);

	if (rightPane->rootIndex().child(0, 0).isValid()) {
		rightPane->setCurrentIndex(rightPane->rootIndex().child(0, 0));
	}
}
