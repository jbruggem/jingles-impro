#include "workspace.h"

Workspace::Workspace(QObject *parent) :
    QObject(parent)
{
    m_stock = new TrackStock(this);
    m_list = new TrackPlaylist(this);
    m_buttons = new TrackPlaylist(this);

}

// add track to stock. Returns the index of the newly created track
int Workspace::addTrack(Track * track){
    QLOG_TRACE() << "Adding track to Stock";
    m_stock->append(track);
    return m_stock->size() - 1;
}

// Moves track from the stock to the list
bool Workspace::stockToList(int index){
    QLOG_TRACE() << "Adding track to playlist from stock";
    return addTo(index,m_list);
}

bool Workspace::stockToButtons(int index){
    return addTo(index,m_buttons);
}

// Moves track from the stock to the list
bool Workspace::stockToList(Track * track){
    return addTo(track,m_list);
}
bool Workspace::stockToButtons(Track * track){
    return addTo(track,m_buttons);
}

bool Workspace::addTo(int index, TrackList * destination){
    return addTo(m_stock->at(index),destination);
}

bool Workspace::addTo(Track * track, TrackList * destination){
    QLOG_TRACE() << "Asserting that track is in stock.";
    if(not this->m_stock->contains(track)) {
        QLOG_FATAL() << "Error: track not in stock!";
        return false;
    } else {
        QLOG_TRACE() << "Adding track to playlist";
        destination->append(track);
        return true;
    }
}

TrackStock * Workspace::getStock(){
    return m_stock;
}

TrackPlaylist * Workspace::getPlaylist(){
    return m_list;
}

TrackPlaylist * Workspace::getButtonlist(){
    return m_buttons;
}

std::ostream& operator<< (std::ostream &out, const Workspace & wsp){
    out << "\n***** Workspace: ";
    out << "\n *** Stock: ";
    out << *wsp.m_stock;
    out << "\n *** Buttons: ";
    out << *wsp.m_buttons;
    out << "\n *** List: ";
    out << *wsp.m_list;
    return out;
}
