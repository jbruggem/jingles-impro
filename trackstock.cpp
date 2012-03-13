#include "trackstock.h"


TrackStock::TrackStock(QObject *parent) :
    QObject(parent)
{
    this->m_tracks = new QList<Track>();
}
