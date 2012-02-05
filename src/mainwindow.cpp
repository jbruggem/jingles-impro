
#include "mainwindow.h"

#include <QAction>
#include <QToolBar>
#include <QFileDialog>
#include "QsLog.h"
#include "buttonpanel.h"
#include "mediaplaylist.h"
#include "nullptr.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {
	QLOG_TRACE() << "MainWindow::MainWindow()";
	createCentralWidget();
	createActions();
	createSideBar();
	
	editMode = false;
	playlist = nullptr;
	
	update();
}

void MainWindow::createCentralWidget() {
	QLOG_TRACE() << "MainWindow::createCentralWidget()";
	buttonPanel = new ButtonPanel;
	setCentralWidget(buttonPanel);
}

void MainWindow::createActions() {
	QLOG_TRACE() << "MainWindow::createActions()";
	addAction = new QAction(tr("&Add"), this);
	addAction->setToolTip(tr("Add tracks to the playlist"));
	addAction->setStatusTip(tr("Add tracks to the playlist"));
	connect(addAction, SIGNAL(triggered()), this, SLOT(addTracks()));
	
	editAction = new QAction(tr("&Edit"), this);
	editAction->setToolTip(tr("Toggle edit mode"));
	editAction->setStatusTip(tr("Toggle edit mode"));
	editAction->setCheckable(true);
	connect(editAction, SIGNAL(triggered()), this, SLOT(toggleEditMode()));
	
	clearAction = new QAction(tr("&Clear"), this);
	clearAction->setToolTip(tr("Clear the playlist"));
	clearAction->setStatusTip(tr("Clear the playlist"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearPlaylist()));
}

void MainWindow::createSideBar() {
	QLOG_TRACE() << "MainWindow::createSideBar()";
	sideBar = new QToolBar(tr("SideBar"));
	sideBar->addAction(addAction);
	sideBar->addAction(editAction);
	sideBar->addAction(clearAction);
	sideBar->setMovable(false);
	addToolBar(Qt::LeftToolBarArea, sideBar);
}

void MainWindow::setPlaylist(MediaPlaylist *playlist) {
	QLOG_TRACE() << "MainWindow::setPlaylist()";
	this->playlist = playlist;
	buttonPanel->clear();
	foreach (const QString &s, *(this->playlist)) {
		buttonPanel->addButton(QFileInfo(s).baseName());
	}
}

void MainWindow::addTracks() {
	QLOG_TRACE() << "MainWindow::addTracks()";
	QStringList paths = QFileDialog::getOpenFileNames(this);
	if (paths.isEmpty()) {
		return;
	}
	playlist->append(paths);
	playlist->print();
	update();
}

void MainWindow::toggleEditMode() {
	QLOG_TRACE() << "MainWindow::toggleEditMode()";
	editMode = !editMode;
}

void MainWindow::clearPlaylist() {
	QLOG_TRACE() << "MainWindow::clearPlaylist()";
	playlist->clear();
	update();
}

void MainWindow::update() {
	QLOG_TRACE() << "MainWindow::update()";
	updateSideBar();
	updateButtonPanel();
}

void MainWindow::updateSideBar() {
	QLOG_TRACE() << "MainWindow::updateSideBar()";
	if (not playlist) {
		return;
	}
	
	if (playlist->isEmpty()) {
		clearAction->setEnabled(false);
	} else {
		clearAction->setEnabled(true);
	}
}

void MainWindow::updateButtonPanel() {
	QLOG_TRACE() << "MainWindow::updateButtonPanel()";
	if (not playlist) {
		return;
	}
	buttonPanel->clear();
	foreach (const QString &s, *playlist) {
		buttonPanel->addButton(QFileInfo(s).baseName());
	}
}
