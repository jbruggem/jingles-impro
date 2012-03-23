#ifndef TRACKPLAYLIST_H
#define TRACKPLAYLIST_H

#include <iostream>
#include <QObject>

class TrackPlaylist : public QObject
{
    Q_OBJECT
public:
    explicit TrackPlaylist(QObject *parent = 0);
    ~TrackPlaylist(){
        std::cout << "deleting TrackPlaylist " << std::endl;
    }

signals:
    
public slots:
    
};

#endif // TRACKPLAYLIST_H
