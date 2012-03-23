#include "trackcollection.h"

TrackCollection::TrackCollection(QObject *parent) :
    QObject(parent)
{
    this->m_tracks = new QList<Track *>();
}

Track * TrackCollection::fetchTrack(int index){
    return m_tracks->value(index);
}

int TrackCollection::add(Track * track){
    this->m_tracks->append(track);
    return this->m_tracks->size()-1;
}
