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
    if(!this->m_stock->hasTrack(track)){
        QLOG_FATAL() << "Error: track not in stock!";
        return false;
    }else{
        QLOG_TRACE() << "Adding track to playlist";
        return 0 <= m_list->add(track);
    }
}


TrackStock * Workspace::getStock(){
    return m_stock;
}

TrackPlaylist * Workspace::getPlaylist(){
    return m_list;
}

std::ostream& operator<< (std::ostream &out, const Workspace & wsp){
    out << "\n***** Workspace: ";
    out << "\n *** Stock: ";
    out << *wsp.m_stock;
    out << "\n *** List: ";
    out << *wsp.m_list;
    return out;
}
