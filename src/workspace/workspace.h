#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <iostream>
#include <QObject>
#include "trackstock.h"
#include "trackplaylist.h"
#include "common.h"


class Workspace : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TrackStock * stock READ getStock)
    Q_PROPERTY(TrackPlaylist * playlist READ getPlaylist)
public:
    Workspace(QObject *parent = 0);
    TrackStock * getStock();
    TrackPlaylist * getPlaylist();

    // add track to stock. Returns the index of the newly created track
    int addTrack(Track * track);

    // Moves track from the stock to the list
    bool stockToList(int index);
    bool stockToList(Track * track);

    ~Workspace(){
         //QLOG_TRACE() << "deleting Workspace ";
    }

    friend std::ostream& operator<< (std::ostream &out, const Workspace & wsp);



private:
    TrackPlaylist * m_list;
    TrackStock * m_stock;

signals:
    
public slots:
    
};

#endif // WORKSPACE_H
