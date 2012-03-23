#ifndef TRACKSTOCK_H
#define TRACKSTOCK_H

#include <QExplicitlySharedDataPointer>
#include <iostream>
#include <QObject>
#include <QList>
#include "track.h"

class TrackStock : public QObject
{
    Q_OBJECT
public:
    explicit TrackStock(QObject *parent = 0);
    void add(Track * track);

    ~TrackStock(){
        std::cout<< "deleting TrackStock"<<std::endl;
    }


private:
    QList<QExplicitlySharedDataPointer<Track> > * m_tracks;

signals:
    
public slots:
    
};

#endif // TRACKSTOCK_H
