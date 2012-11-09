
#include "testui.h"

#include <QGridLayout>
#include "playlistwidget.h"
#include "tracklist.h"

TestUi::TestUi(QWidget *parent)
    : QWidget (parent) {

    playListWidget = new PlayListWidget;
    
    setLayout(new QGridLayout);
    layout()->addWidget(playListWidget);
}

void TestUi::setTrackList(const TrackList *list) {
    playListWidget->setTrackList(list);
}

