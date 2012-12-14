
#include "hslidelayout.h"

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "QsLog.h"

/// \todo handle show/hide status of widgets
/// \todo handle stretch factor

HSlideLayout::HSlideLayout(QWidget *parent)
    : QHBoxLayout(parent) {
    QLOG_TRACE() << "HSlideLayout::HSlideLayout()";
    
    duration = 0;
    easingCurve = QEasingCurve::Linear;
    animation = new QParallelAnimationGroup;
    transitionBusy = false;
    
    connect(animation, SIGNAL(finished()), this, SLOT(transitionFinishedSlot()));
}

/**
 * Makes the widget passed as parameter visible, hiding the others.
 * \return true on success, false otherwise (a transition is refused if another is in progress)
 */
bool HSlideLayout::switchTo(QWidget *w, bool animate) {
    return switchTo(QWidgetList() << w, animate);
}


/**
 * Makes the widgets passed as parameters visible, hiding the others.
 * \return true on success, false otherwise (a transition is refused if another is in progress)
 */
bool HSlideLayout::switchTo(QWidgetList &l, bool animate) {
    QLOG_TRACE() << "HSlideLayout::switchTo()";
    
    if (not animate) {
        // scan all child widgets
        for (int i = 0; i < count(); i++) {
            QWidget *w = itemAt(i)->widget();
            if (l.contains(w)) {
                // widgets that need to be displayed
                w->setMaximumWidth(QWIDGETSIZE_MAX);
            } else {
                // widgets that need to be hidden
                w->setMaximumWidth(0);
            }
        }
        return true;
    }
    
    if (transitionBusy) {
        return false;
    }
    transitionBusy = true;
    
    QWidgetList myWidgets;
    for (int i = 0; i < count(); i++) {
        myWidgets.append(itemAt(i)->widget());
    }
    
    // Find number of widgets that need to be displayed,
    // ignoring the ones that are in the provided list but aren't children of this layout.
    int nbShown = 0;
    int totalWidth = 0;
    for (int i = 0; i < count(); i++) {
        QWidget *w = itemAt(i)->widget();
        if (l.contains(w)) {
            nbShown++;
        }
        totalWidth += w->width();
    }
    
    // scan all child widgets
    for (int i = 0; i < count(); i++) {
        QWidget *w = itemAt(i)->widget();
        if (l.contains(w)) {
            // widgets that need to be displayed
            QPropertyAnimation *pa = new QPropertyAnimation(w, "maximumWidth");
            pa->setDuration(duration);
            pa->setStartValue(w->width());
            pa->setEndValue(totalWidth / nbShown);
            pa->setEasingCurve(easingCurve);
            
            animation->addAnimation(pa);
        } else {
            // widgets that need to be hidden
            QPropertyAnimation *pa = new QPropertyAnimation(w, "maximumWidth");
            pa->setDuration(duration);
            pa->setStartValue(w->width());
            pa->setEndValue(0);
            pa->setEasingCurve(easingCurve);
            
            animation->addAnimation(pa);
        }
    }
    
    animation->start();
    
    return true;
}

void HSlideLayout::transitionFinishedSlot() {
    QLOG_TRACE() << "HSlideLayout::transitionFinishedSlot()";
    
    animation->clear();
    
    for (int i = 0; i < count(); i++) {
        QWidget *w = itemAt(i)->widget();
        if (w->maximumWidth()) {
            w->setMaximumWidth(QWIDGETSIZE_MAX);
        }
    }
    transitionBusy = false;
    emit transitionFinished();
}

void HSlideLayout::setDuration(int ms) {
    duration = ms;
}

void HSlideLayout::setEasingCurve(QEasingCurve::Type t) {
    easingCurve = t;
}

