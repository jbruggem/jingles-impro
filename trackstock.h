#ifndef TRACKSTOCK_H
#define TRACKSTOCK_H

#include <QObject>
#include <QList>
#include "track.h"

class TrackStock : public QObject
{
    Q_OBJECT
public:
    explicit TrackStock(QObject *parent = 0);

private:
    QList<Track> * m_tracks;

signals:
    
public slots:
    
};

#endif // TRACKSTOCK_H
