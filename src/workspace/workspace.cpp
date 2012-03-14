#include "workspace.h"

Workspace::Workspace(QObject *parent) :
    QObject(parent)
{
    m_stock = new TrackStock();
    m_list = new TrackPlaylist();

}


TrackStock * Workspace::getStock(){
    return m_stock;
}
