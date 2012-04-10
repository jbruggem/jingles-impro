
#include "editwidget.h"

#include <QGridLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>
#include <QTimer>
#include <QShortcut>
#include "QsLog.h"

// todo enable keyboard navigation in right pane
// todo add navigation buttons
// todo add filter

EditWidget::EditWidget(QWidget *parent)
	: QWidget(parent) {

	// set up the timer
	refreshDelayTimer = new QTimer(this);
	refreshDelayTimer->setSingleShot(true);
	refreshDelay = 0;

	leftPaneFolder = QDir::rootPath();

	// set up the left pane
	dirsOnlyModel = new QFileSystemModel;
	dirsOnlyModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dirsOnlyModel->setRootPath(leftPaneFolder);
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
	fileModel->setRootPath(leftPaneFolder);
	rightPane = new QTreeView;
	rightPane->setModel(fileModel);
	rightPane->setSelectionMode(QAbstractItemView::ExtendedSelection);
	rightPaneUpdate(fileModel->rootPath());

	// set up the layout
	layout = new QGridLayout;
	layout->addWidget(leftPane, 0, 0);
	layout->addWidget(rightPane, 0, 1);
	setLayout(layout);

	// set up keyboard shortcuts
	shortcut_backspace = new QShortcut(QKeySequence("Backspace"), this);

	// connect signals to slots
	connect(leftPane->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(leftPaneItemSelected(const QModelIndex &)));
	connect(rightPane, SIGNAL(activated(const QModelIndex &)), this, SLOT(rightPaneItemActivated(const QModelIndex &)));
	// connect(fileModel, SIGNAL(directoryLoaded(const QString &)), this, SLOT(rightPaneSelectFirstRow()));
	connect(refreshDelayTimer, SIGNAL(timeout()), this, SLOT(rightPaneUpdate()));
	connect(shortcut_backspace, SIGNAL(activated()), this, SLOT(navigateUp()));
}

void EditWidget::setRefreshDelay(int delay) {
	refreshDelay = delay;
}

int EditWidget::getRefreshDelay() const {
	return refreshDelay;
}

void EditWidget::leftPaneItemSelected(const QModelIndex &index) {
	QLOG_TRACE() << "EditWidget::leftPaneItemSelected()";
	leftPaneFolder = reinterpret_cast<const QFileSystemModel *>(index.model())->fileInfo(index).absoluteFilePath();
	QLOG_TRACE() << "directory:" << leftPaneFolder;

	refreshDelayTimer->start(refreshDelay);
}

void EditWidget::rightPaneItemActivated(const QModelIndex &index) {
	QLOG_TRACE() << "EditWidget::rightPaneItemActivated()";
	QString openDir(reinterpret_cast<const QFileSystemModel *>(index.model())->fileInfo(index).absoluteFilePath());
	QLOG_TRACE() << "directory:" << openDir;
	// rightPaneUpdate(openDir);
	leftPaneUpdate(openDir);
}

void EditWidget::leftPaneUpdate(const QString &dir) {
	QLOG_TRACE() << "EditWidget::leftPaneUpdate()";

	leftPane->setCurrentIndex(dirsOnlyModel->index(dir));
}

void EditWidget::rightPaneUpdate() {
	rightPaneUpdate(leftPaneFolder);
}

void EditWidget::rightPaneUpdate(const QString &dir) {
	QLOG_TRACE() << "EditWidget::rightPaneUpdate()";
	QLOG_TRACE() << "rows:" << fileModel->rowCount(fileModel->index(dir));

	bool populatedAndNotEmpty = true;
	// if the folder contents have not yet been populated, we connect to the directoryLoaded() signal
	if (not fileModel->rowCount(fileModel->index(dir))) {
		populatedAndNotEmpty = false;
		connect(fileModel, SIGNAL(directoryLoaded(const QString &)), this, SLOT(rightPaneUpdated()));
	}
	// make sure that all folders are collapsed whenever the view changes folder
	rightPane->collapseAll();
	rightPane->setRootIndex(fileModel->setRootPath(dir));
	if (populatedAndNotEmpty) {
		rightPaneUpdated();
	}
}

void EditWidget::rightPaneUpdated() {
	QLOG_TRACE() << "EditWidget::rightPaneUpdated()";
	disconnect(fileModel, SIGNAL(directoryLoaded(const QString &)), 0, 0);
	rightPaneSelectFirstRow();
}

void EditWidget::rightPaneSelectFirstRow() {
	QLOG_TRACE() << "EditWidget::rightPaneSelectFirstRow()";

	// the model is not sorted by default, meaning the first child is not the first entry in the view.
	fileModel->sort(0, Qt::AscendingOrder);

	if (rightPane->rootIndex().child(0, 0).isValid()) {
		rightPane->setCurrentIndex(rightPane->rootIndex().child(0, 0));
	}
}

void EditWidget::navigateUp() {
	QLOG_TRACE() << "EditWidget::navigateUp()";
	if (leftPane->currentIndex().parent().isValid()) {
		leftPaneFolder = dirsOnlyModel->fileInfo(leftPane->currentIndex().parent()).absoluteFilePath();
		leftPaneUpdate(leftPaneFolder);
		// rightPaneUpdate(leftPaneFolder);
	}
}
