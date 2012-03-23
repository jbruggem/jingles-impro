#ifndef TRACKSTOCK_H
#define TRACKSTOCK_H

#include <QExplicitlySharedDataPointer>
#include <iostream>
#include <QObject>
#include <QList>
#include "trackcollection.h"
#include "track.h"
#include "common.h"

class TrackStock : public TrackCollection
{
    public:
        explicit TrackStock(QObject *parent = 0);

        ~TrackStock(){
            //QLOG_TRACE() << "deleting TrackStock";
    }


private:

signals:
    
public slots:
    
};

#endif // TRACKSTOCK_H
