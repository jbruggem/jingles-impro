#include "workspace.h"

Workspace::Workspace(QObject *parent) :
    QObject(parent)
{
    m_stock = new TrackStock(this);
    m_list = new TrackPlaylist(this);

}

// add track to stock. Returns the index of the newly created track
int Workspace::addTrack(Track * track){
    return this->m_stock->add(track);
}

// Moves track from the stock to the list
bool Workspace::stockToList(int index){
    this->stockToList(m_stock->fetchTrack(index));
    return true;
}

// Moves track from the stock to the list
bool Workspace::stockToList(Track * track){
    return false;
}


TrackStock * Workspace::getStock(){
    return m_stock;
}

TrackPlaylist * Workspace::getPlaylist(){
    return m_list;
}
