#ifndef TRACKCOLLECTION_H
#define TRACKCOLLECTION_H

#include <QObject>
#include "track.h"
#include "common.h"

class TrackCollection : public QObject
{
    Q_OBJECT
public:
    explicit TrackCollection(QObject *parent = 0);
    int add(Track * track);

    Track * fetchTrack(int index);

    ~TrackCollection(){
        QLOG_TRACE() << "deleting a TrackCollection";
    }


private:
    QList<Track *> * m_tracks;

    
signals:
    
public slots:
    
};

#endif // TRACKCOLLECTION_H
