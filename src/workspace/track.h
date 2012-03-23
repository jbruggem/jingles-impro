#ifndef TRACK_H
#define TRACK_H

#include <sstream>
#include <string>
#include <QObject>
#include "common.h"

class Track : public QObject
{

    Q_OBJECT
    Q_PROPERTY(const QString * path READ getPath)
    Q_PROPERTY(bool loopEnabled READ isLoopEnabled)
    Q_PROPERTY(int startTime READ getStartTime)
    Q_PROPERTY(int endTime READ getEndTime)
    Q_PROPERTY(int fadeInDuration READ getFadeInDuration)
    Q_PROPERTY(int fadeOutDuration READ getFadeOutDuration)
public:
    ~Track(){
        QLOG_TRACE() << "deleting Track[" << this->path << "|"
                     << this->startTime
                     << "-"
                     << this->endTime
                     << "]";
    }


    explicit Track(const Track& track);

    explicit Track(
            const QString &url,
            bool loop,
            int startTime, // milliseconds
            int endTime,
            int fadeInDuration,
            int fadeOutDuration,
            QObject *parent = 0);
    explicit Track(const QString &url,QObject *parent = 0);
    explicit Track(QObject *parent = 0);


    const QString * getPath() const{return &path;}
    bool isLoopEnabled() const{return loopEnabled;}
    int getStartTime() const{return startTime;}
    int getEndTime() const{return endTime;}
    int getFadeInDuration() const{return fadeInDuration;}
    int getFadeOutDuration() const{return fadeOutDuration;}

private:
    QString path;
    bool loopEnabled;
    int startTime; // milliseconds
    int endTime;
    int fadeInDuration;
    int fadeOutDuration;

signals:
    
public slots:
    
};

#endif // TRACK_H
