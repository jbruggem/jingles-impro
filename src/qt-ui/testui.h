
#ifndef TESTUI_H_
#define TESTUI_H_

#include <QWidget>

class QPushButton;
class StockListWidget;
class PlayListWidget;
class TrackList;
class QPropertyAnimation;
class QParallelAnimationGroup;
class HSlideLayout;

class TestUi : public QWidget {
    
    Q_OBJECT
    
    public:
        TestUi(QWidget *parent = 0);
        void setTrackList(TrackList *);
    private slots:
        void buttonPressed();
    private:
        QPushButton     *button;
        StockListWidget *w1;
        PlayListWidget  *w2;
        PlayListWidget  *w3;
        
        HSlideLayout *slideLayout;
        
        // animations
        enum State {
            ONE,
            TWO
        } state;
};

#endif
