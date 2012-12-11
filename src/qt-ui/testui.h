
#ifndef TESTUI_H_
#define TESTUI_H_

#include <QWidget>

class QPushButton;
class StockListWidget;
class PlayListWidget;
class TrackList;
class QPropertyAnimation;
class QParallelAnimationGroup;

class TestUi : public QWidget {
    
    Q_OBJECT
    
    public:
        TestUi(QWidget *parent = 0);
        void setTrackList(TrackList *);
    private slots:
        void buttonPressed();
        void transitionFinished();
    private:
        QPushButton     *button;
        StockListWidget *w1;
        PlayListWidget  *w2;
        PlayListWidget  *w3;
        
        // animations
        enum State {
            W1,
            W3
        } state;
        QPropertyAnimation *w1Width;
        QPropertyAnimation *w3Width;
        QParallelAnimationGroup *transition;
};

#endif
