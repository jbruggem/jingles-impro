
#include "editwidget.h"

#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSplitter>
#include "stocklistwidget.h"
#include "playlistwidget.h"
#include "tracklist.h"

EditWidget::EditWidget(QWidget *parent)
    : QWidget(parent) {

    // set up the StockList
    stockListWidget   = new StockListWidget;
    stockListGroupBox = new QGroupBox(tr("Library"));
    stockListGroupBox->setLayout(new QHBoxLayout);
    stockListGroupBox->layout()->addWidget(stockListWidget);
    
    // set up the button
    addButton = new QPushButton("-->");
    stockListGroupBox->layout()->addWidget(addButton);
    
    // set up the PlayList
    playListWidget   = new PlayListWidget;
    playListGroupBox = new QGroupBox(tr("Playlist"));
    playListGroupBox->setLayout(new QHBoxLayout);
    playListGroupBox->layout()->addWidget(playListWidget);
    
    // set up the splitter
    splitter = new QSplitter;
    splitter->addWidget(stockListGroupBox);
    splitter->setStretchFactor(0, 1);
    splitter->addWidget(playListGroupBox);
    splitter->setStretchFactor(1, 2);

    // set up the layout
    setLayout(new QGridLayout);
    layout()->addWidget(splitter);
    layout()->setContentsMargins(0, 0, 0, 0);

    // connect signals and slots
    connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
}

void EditWidget::update(TrackList *stockList, TrackList *playList) {
    stockListWidget->setTrackList(stockList);
    playListWidget->setTrackList(playList);
}

void EditWidget::addButtonClicked() {
    QLOG_TRACE() << "EditWidget::addButtonClicked()";
    // trackListModel->addTracks(explorer->getSelection());
}
