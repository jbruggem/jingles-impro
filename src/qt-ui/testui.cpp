
#include "testui.h"

#include <QGridLayout>
#include "stocklistwidget.h"
#include "tracklist.h"

TestUi::TestUi(QWidget *parent)
    : QWidget (parent) {

    stockListWidget = new StockListWidget;
    
    setLayout(new QGridLayout);
    layout()->addWidget(stockListWidget);
}

void TestUi::setTrackList(const TrackList *list) {
    stockListWidget->setTrackList(list);
}

