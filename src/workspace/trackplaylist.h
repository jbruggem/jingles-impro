#ifndef TRACKPLAYLIST_H
#define TRACKPLAYLIST_H

#include <iostream>
#include <QObject>
#include "common.h"
#include "trackcollection.h"

class TrackPlaylist : public TrackCollection
{
public:
    explicit TrackPlaylist(QObject *parent = 0);
    ~TrackPlaylist(){
        QLOG_TRACE() << "deleting TrackPlaylist ";
    }
private:

signals:
    
public slots:
    
};

#endif // TRACKPLAYLIST_H
