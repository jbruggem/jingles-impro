
#include "twopaneexplorer.h"

#include <QFileSystemModel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QModelIndex>
#include <QShortcut>
#include <QSplitter>
#include <QStringList>
#include <QTimer>
#include <QTreeView>
#include "history.h"
#include "QsLog.h"

// todo clean up code, because it is a mess. No idea why it even works.
// todo add navigation buttons
// todo add filter

TwoPaneExplorer::TwoPaneExplorer(QWidget *parent)
	: QWidget(parent) {

	// set up the timer
	refreshDelayTimer = new QTimer(this);
	refreshDelayTimer->setSingleShot(true);
	refreshDelay = 0;

	// set default behaviour of the backspace key to Go To Parent Folder
	backspaceIsHistoryBack = false;

	// set up the filter editor
	filterLabel  = new QLabel(tr("Filter"));
	filterEditor = new QLineEdit("*.mp3, *.flac");
	QHBoxLayout *filterLayout = new QHBoxLayout;
	filterLayout->addWidget(filterLabel);
	filterLayout->addWidget(filterEditor);

	// initialize navigation history
	history.add(QDir::rootPath());
	leftPaneFolder = history.getCurrent();

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
	QLOG_TRACE() << "filters:";
	QStringList l = filterEditor->text().split(QRegExp("[,;\\s]+"), QString::SkipEmptyParts);
	for (int i = 0; i < l.length(); i++) {
		QLOG_TRACE() << l.at(i);
	}
	fileModel->setNameFilters(l);
	// items that don't pass the filter are hidden rather than disabled
	fileModel->setNameFilterDisables(false);
	rightPane = new QTreeView;
	rightPane->setModel(fileModel);
	// only show first column (folder names)
	for (int i = 1; i < fileModel->columnCount(); i++) {
		rightPane->hideColumn(i);
	}
	// hide the column headers
	rightPane->setHeaderHidden(true);
	rightPane->setSelectionMode(QAbstractItemView::ExtendedSelection);
	rightPaneUpdate(fileModel->rootPath());

	// set up the splitter
	paneSplitter = new QSplitter;
	paneSplitter->addWidget(leftPane);
	paneSplitter->addWidget(rightPane);

	// set up the layout
	QGridLayout *widgetLayout = new QGridLayout;
	setLayout(widgetLayout);
	widgetLayout->setContentsMargins(0, 0, 0, 0);
	widgetLayout->addWidget(paneSplitter, 0, 0);
	widgetLayout->addLayout(filterLayout, 1, 0);

	// set up keyboard shortcuts
	shortcut_backspace = new QShortcut(QKeySequence("Backspace"), this);
	shortcut_altLeft   = new QShortcut(QKeySequence("Alt+Left"), this);
	shortcut_altRight  = new QShortcut(QKeySequence("Alt+Right"), this);
	shortcut_altUp     = new QShortcut(QKeySequence("Alt+Up"), this);

	// connect signals to slots
	connect(leftPane->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(leftPaneItemSelected(const QModelIndex &)));
	connect(rightPane, SIGNAL(activated(const QModelIndex &)), this, SLOT(rightPaneItemActivated(const QModelIndex &)));
	connect(refreshDelayTimer, SIGNAL(timeout()), this, SLOT(rightPaneUpdate()));
	connect(shortcut_backspace, SIGNAL(activated()), this, SLOT(navigateUp()));
	connect(shortcut_altUp, SIGNAL(activated()), this, SLOT(navigateUp()));
	connect(shortcut_altLeft, SIGNAL(activated()), this, SLOT(navigateBack()));
	connect(shortcut_altRight, SIGNAL(activated()), this, SLOT(navigateForward()));
	connect(filterEditor, SIGNAL(textChanged(const QString &)), this, SLOT(filterChanged(const QString &)));
}

void TwoPaneExplorer::setRefreshDelay(int delay) {
	refreshDelay = delay;
}

int TwoPaneExplorer::getRefreshDelay() const {
	return refreshDelay;
}

void TwoPaneExplorer::setBackspaceToHistoryBack(bool val) {
	backspaceIsHistoryBack = val;
	if (val) {
		shortcut_backspace->disconnect();
		connect(shortcut_backspace, SIGNAL(activated()), this, SLOT(navigateBack()));
	} else {
		shortcut_backspace->disconnect();
		connect(shortcut_backspace, SIGNAL(activated()), this, SLOT(navigateUp()));
	}
}

bool TwoPaneExplorer::isBackspaceHistoryBack() const {
	return backspaceIsHistoryBack;
}

void TwoPaneExplorer::leftPaneItemSelected(const QModelIndex &index) {
	QLOG_TRACE() << "EditWidget::leftPaneItemSelected()";
	leftPaneFolder = reinterpret_cast<const QFileSystemModel *>(index.model())->fileInfo(index).absoluteFilePath();
	QLOG_TRACE() << "directory:" << leftPaneFolder;
	history.add(leftPaneFolder);

	refreshDelayTimer->start(refreshDelay);
}

void TwoPaneExplorer::rightPaneItemActivated(const QModelIndex &index) {
	QLOG_TRACE() << "EditWidget::rightPaneItemActivated()";
	leftPaneFolder = reinterpret_cast<const QFileSystemModel *>(index.model())->fileInfo(index).absoluteFilePath();
	QLOG_TRACE() << "directory:" << leftPaneFolder;
	history.add(leftPaneFolder);
	leftPaneUpdate(leftPaneFolder);
	rightPaneUpdate(leftPaneFolder);
}

void TwoPaneExplorer::leftPaneUpdate(const QString &dir) {
	QLOG_TRACE() << "EditWidget::leftPaneUpdate()";

	disconnect(leftPane->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(leftPaneItemSelected(const QModelIndex &)));
	leftPane->setCurrentIndex(dirsOnlyModel->index(dir));
	connect(leftPane->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(leftPaneItemSelected(const QModelIndex &)));
}

void TwoPaneExplorer::rightPaneUpdate() {
	rightPaneUpdate(leftPaneFolder);
}

void TwoPaneExplorer::rightPaneUpdate(const QString &dir) {
	QLOG_TRACE() << "EditWidget::rightPaneUpdate()";

	bool populatedAndNotEmpty = true;
	// if the folder contents have not yet been populated, we connect to the directoryLoaded() signal
	if (not fileModel->rowCount(fileModel->index(dir))) {
		QLOG_TRACE() << "folder not yet populated";
		populatedAndNotEmpty = false;
		connect(fileModel, SIGNAL(directoryLoaded(const QString &)), this, SLOT(rightPaneUpdated()));
	}
	// make sure that all folders are collapsed whenever the view changes folder
	rightPane->collapseAll();

	// todo: this line should maybe be changed into:
	// rightPane->setRootIndex(fileModel->index(dir));
	rightPane->setRootIndex(fileModel->setRootPath(dir));

	// if the folder contents have already been populated
	// the directoryLoaded() signal will not come, so we call
	// rightPaneUpdated() directly
	if (populatedAndNotEmpty) {
		QLOG_TRACE() << "folder already populated";
		rightPaneUpdated();
	}
}

void TwoPaneExplorer::rightPaneUpdated() {
	QLOG_TRACE() << "EditWidget::rightPaneUpdated()";
	disconnect(fileModel, SIGNAL(directoryLoaded(const QString &)), 0, 0);
	rightPaneSelectFirstRow();
}

void TwoPaneExplorer::rightPaneSelectFirstRow() {
	QLOG_TRACE() << "EditWidget::rightPaneSelectFirstRow()";

	// the model is not sorted by default, meaning the first child is not the first entry in the view.
	fileModel->sort(0, Qt::AscendingOrder);

	if (rightPane->rootIndex().child(0, 0).isValid()) {
		rightPane->setCurrentIndex(rightPane->rootIndex().child(0, 0));
	}
}

void TwoPaneExplorer::navigateUp() {
	QLOG_TRACE() << "EditWidget::navigateUp()";
	if (leftPane->currentIndex().parent().isValid()) {
		QModelIndex childIndex = rightPane->rootIndex();
		leftPaneFolder = dirsOnlyModel->fileInfo(leftPane->currentIndex().parent()).absoluteFilePath();
		history.add(leftPaneFolder);
		leftPaneUpdate(leftPaneFolder);
		rightPaneUpdate(leftPaneFolder);
		// put selection on folder we are coming from
		rightPane->setCurrentIndex(childIndex);
	}
}

void TwoPaneExplorer::navigateBack() {
	QLOG_TRACE() << "EditWidget::navigateBack()";
	if (history.canGoBack()) {
		// store the folder we are coming from
		QModelIndex previousIndex = rightPane->rootIndex();
		leftPaneFolder = history.back();
		leftPaneUpdate(leftPaneFolder);
		rightPaneUpdate(leftPaneFolder);

		// if we are going up one level,
		// put selection on folder we are coming from (like in navigateUp())
		if (fileModel->index(leftPaneFolder) == previousIndex.parent()) {
			rightPane->setCurrentIndex(previousIndex);
		}
	}
}

void TwoPaneExplorer::navigateForward() {
	QLOG_TRACE() << "EditWidget::navigateForward()";
	leftPaneFolder = history.forward();
	leftPaneUpdate(leftPaneFolder);
	rightPaneUpdate(leftPaneFolder);
}

QStringList TwoPaneExplorer::getSelection() const {
	QLOG_TRACE() << "TwoPaneExplorer::getSelection()";
	QStringList selectedItems;
	QModelIndexList indexList = rightPane->selectionModel()->selectedRows();
	for (int i = 0; i < indexList.length(); i++) {
		selectedItems.append(fileModel->fileInfo(indexList.at(i)).absoluteFilePath());
		QLOG_TRACE() << "selected:" << selectedItems.at(i);
	}
	return selectedItems;
}

void TwoPaneExplorer::filterChanged(const QString &newString) {
	QLOG_TRACE() << "TwoPaneExplorer::filterChanged()";
	QStringList l = newString.split(QRegExp("[,;\\s]+"), QString::SkipEmptyParts);
	for (int i = 0; i < l.length(); i++) {
		QLOG_TRACE() << l.at(i);
	}
	fileModel->setNameFilters(l);
}
