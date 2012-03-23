#include "trackcollection.h"

TrackCollection::TrackCollection(QObject *parent) :
    QObject(parent)
{
    this->m_tracks = new QList<Track *>();
}

bool * TrackCollection::hasTrack(Track * const &track){
    QLOG_TRACE() << "Collection: hasTrack";
    return m_tracks->contains(track);
}

Track * TrackCollection::fetchTrack(int index){
    QLOG_TRACE() << "Collection: fetchTrack";
    return m_tracks->value(index);
}

int TrackCollection::add(Track * track){
    QLOG_TRACE() << "Collection: add";
    this->m_tracks->append(track);
    return this->m_tracks->size()-1;
}
