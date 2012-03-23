#include "workspace.h"

Workspace::Workspace(QObject *parent) :
    QObject(parent)
{
    m_stock = new TrackStock(this);
    m_list = new TrackPlaylist(this);

}


TrackStock * Workspace::getStock(){
    return m_stock;
}
