
#include "testui.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "stocklistwidget.h"
#include "playlistwidget.h"
#include "tracklist.h"

TestUi::TestUi(QWidget *parent)
    : QWidget (parent) {
        
    w1 = new StockListWidget;
    w2 = new PlayListWidget;
    w3 = new PlayListWidget;
    
    button = new QPushButton(tr("switch"));
    
    QHBoxLayout *l = new QHBoxLayout;
    setLayout(l);
    l->addWidget(button);
    l->addWidget(w1);
    l->addWidget(w2);
    l->addWidget(w3);
    
    state = W3;
    w1->setMaximumWidth(0);
    
    // setup animations
    w1Width = new QPropertyAnimation(w1, "maximumWidth");
    w1Width->setDuration(500);
    w1Width->setStartValue(0);
    // end value to be defined when starting the transition
    w1Width->setEasingCurve(QEasingCurve::InOutQuad);
    
    w3Width = new QPropertyAnimation(w3, "maximumWidth");
    w3Width->setDuration(500);
    // start value to be defined when starting the transition
    w3Width->setEndValue(0);
    w3Width->setEasingCurve(QEasingCurve::InOutQuad);
    
    transition = new QParallelAnimationGroup;
    transition->addAnimation(w1Width);
    transition->addAnimation(w3Width);
    
    connect(button,     SIGNAL(clicked()),  this, SLOT(buttonPressed()));
    connect(transition, SIGNAL(finished()), this, SLOT(transitionFinished()));
}

void TestUi::setTrackList(TrackList *list) {
    w1->setTrackList(list);
    w2->setTrackList(list);
    w3->setTrackList(list);
}

void TestUi::buttonPressed() {
    QLOG_TRACE() << "TestUi::buttonPressed()";
    
    if (state == W3) {
        w1Width->setEndValue(w3->width());
        w3Width->setStartValue(w3->width());
        button->setEnabled(false);
        state = W1;
        transition->setDirection(QAbstractAnimation::Forward);
        transition->start();
        
    } else if (state == W1) {
        w1Width->setEndValue(w1->width());
        w3Width->setStartValue(w1->width());
        button->setEnabled(false);
        state = W3;
        transition->setDirection(QAbstractAnimation::Backward);
        transition->start();
    }
}

void TestUi::transitionFinished() {
    QLOG_TRACE() << "TestUi::transitionFinished()";
    
    if (state == W1) {
        w1->setMaximumWidth(QWIDGETSIZE_MAX);
    } else if (state == W3) {
        w3->setMaximumWidth(QWIDGETSIZE_MAX);
    }
    button->setEnabled(true);
}

