
#ifndef HSLIDELAYOUT_H
#define HSLIDELAYOUT_H

#include <QHBoxLayout>
#include <QWidget>
#include <QEasingCurve>

class QParallelAnimationGroup;

class HSlideLayout : public QHBoxLayout {
    
    Q_OBJECT
    
    public:
        HSlideLayout(QWidget *parent = 0);
        bool switchTo(QWidget *, bool animate = true);
        bool switchTo(QWidgetList &, bool animate = true);
        void setDuration(int);
        void setEasingCurve(QEasingCurve::Type);
        
    signals:
        void transitionFinished();
    protected slots:
        void transitionFinishedSlot();
    protected:
        QParallelAnimationGroup *animation;
        int duration;
        QEasingCurve::Type easingCurve;
        bool transitionBusy;
};

#endif

