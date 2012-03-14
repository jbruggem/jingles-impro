#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QObject>
#include "trackstock.h"
#include "trackplaylist.h"

class Workspace : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TrackStock * stock READ getStock)
public:
    Workspace(QObject *parent = 0);
    TrackStock * getStock();


private:
    TrackPlaylist * m_list;
    TrackStock * m_stock;

signals:
    
public slots:
    
};

#endif // WORKSPACE_H
