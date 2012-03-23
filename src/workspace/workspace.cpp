#include "workspace.h"

Workspace::Workspace(QObject *parent) :
    QObject(parent)
{
    m_stock = new TrackStock(this);
    m_list = new TrackPlaylist(this);

}

// add track to stock. Returns the index of the newly created track
int Workspace::addTrack(Track * track){
    QLOG_TRACE() << "Adding track to Stock";
    return this->m_stock->add(track);
}

// Moves track from the stock to the list
bool Workspace::stockToList(int index){
    QLOG_TRACE() << "Adding track to playlist from stock";
    this->stockToList(m_stock->fetchTrack(index));
    return true;
}

// Moves track from the stock to the list
bool Workspace::stockToList(Track * track){
    QLOG_TRACE() << "Asserting that track is in stock.";
    assert(this->m_stock->hasTrack(track));
    // TODO    QLOG_TRACE() << "Adding track to playlist";
    return 0 <= m_list->add(track);
}


TrackStock * Workspace::getStock(){
    return m_stock;
}

TrackPlaylist * Workspace::getPlaylist(){
    return m_list;
}
