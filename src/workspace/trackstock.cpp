#include "trackstock.h"


TrackStock::TrackStock(QObject *parent) :
    QObject(parent)
{
    this->m_tracks = new QList<QExplicitlySharedDataPointer<Track> >();
}

void TrackStock::add(Track * track){
    QExplicitlySharedDataPointer<Track> ptr = QExplicitlySharedDataPointer(track);
    this->m_tracks->append(ptr);
}
