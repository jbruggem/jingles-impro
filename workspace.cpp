#include "workspace.h"

Workspace::Workspace(QObject *parent) :
    QObject(parent)
{
}


TrackStock * Workspace::getStock(){
    return m_stock;
}
