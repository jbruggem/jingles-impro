#include "trackstock.h"


TrackStock::TrackStock(QObject *parent) :
    QObject(parent)
{
    this->m_tracks = new QList<Track>();
}

void TrackStock::add(Track & track){
    this->m_tracks->append(track);
}
