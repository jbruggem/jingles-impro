
#include "testui.h"

#include <QGridLayout>
#include "stocklistwidget.h"
#include "playlistwidget.h"
#include "tracklist.h"

TestUi::TestUi(QWidget *parent)
    : QWidget (parent) {

    stockListWidget = new StockListWidget;
    playListWidget  = new PlayListWidget;
    
    setLayout(new QGridLayout);
    // layout()->addWidget(stockListWidget);
    layout()->addWidget(playListWidget);
}

void TestUi::setTrackList(TrackList *list) {
    stockListWidget->setTrackList(list);
    playListWidget->setTrackList(list);
}

