#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <iostream>
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

    ~Workspace(){
        std::cout << "deleting Workspace " << std::endl;
    }

private:
    TrackPlaylist * m_list;
    TrackStock * m_stock;

signals:
    
public slots:
    
};

#endif // WORKSPACE_H
