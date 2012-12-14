
#include "testui.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "stocklistwidget.h"
#include "playlistwidget.h"
#include "tracklist.h"
#include "hslidelayout.h"

TestUi::TestUi(QWidget *parent)
    : QWidget (parent) {
        
    w1 = new StockListWidget;
    w2 = new PlayListWidget;
    w3 = new PlayListWidget;
    
    slideLayout = new HSlideLayout;
    slideLayout->addWidget(w1);
    slideLayout->addWidget(w2);
    slideLayout->addWidget(w3);
    slideLayout->setDuration(500);
    slideLayout->setEasingCurve(QEasingCurve::InOutCirc);
    
    button = new QPushButton(tr("switch"));
    
    QHBoxLayout *l = new QHBoxLayout;
    setLayout(l);
    l->addWidget(button);
    l->addLayout(slideLayout);
    
    state = ONE;
    slideLayout->switchTo(w1, false);  // no animation
    
    connect(button,      SIGNAL(clicked()),  this, SLOT(buttonPressed()));
}

void TestUi::setTrackList(TrackList *list) {
    w1->setTrackList(list);
    w2->setTrackList(list);
    w3->setTrackList(list);
}

void TestUi::buttonPressed() {
    QLOG_TRACE() << "TestUi::buttonPressed()";
    
    switch (state) {
        case ONE:
            if (slideLayout->switchTo(QWidgetList() << w2 << w3)) {
                state = TWO;
            }
            break;
        case TWO:
            if (slideLayout->switchTo(QWidgetList() << w1)) {
                state = ONE;
            }
            break;
    }
}

