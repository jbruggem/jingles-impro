
#ifndef TESTUI_H_
#define TESTUI_H_

#include <QWidget>

class PlayListWidget;
class TrackList;

class TestUi : public QWidget {
    public:
        TestUi(QWidget *parent = 0);
        void setTrackList(const TrackList *);
    private:
        PlayListWidget *playListWidget;
};

#endif
