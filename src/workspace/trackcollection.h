#ifndef TRACKCOLLECTION_H
#define TRACKCOLLECTION_H

#include <QObject>
#include "track.h"
#include "common.h"
#include <iostream>

class TrackCollection : public QObject
{
    Q_OBJECT
public:
    explicit TrackCollection(QObject *parent = 0);
    int add(Track * track);

    Track * fetchTrack(int index);
    bool hasTrack(Track * const &track);

    ~TrackCollection(){
        //QLOG_TRACE() << "deleting a TrackCollection";
    }

    friend std::ostream& operator<< (std::ostream &out, TrackCollection &coll){
        Track * t;
        for(int i=0; i<coll.m_tracks->size(); i++){
            t = coll.m_tracks->value(i);
            out << "\n   Track[" << t->getPath().toStdString() << "|"
                                 << t->getStartTime()
                                 << "-"
                                 << t->getEndTime()
                                 << "]";
        }
        return out;
    }


private:
    QList<Track *> * m_tracks;

    
signals:
    
public slots:
    
};

#endif // TRACKCOLLECTION_H
