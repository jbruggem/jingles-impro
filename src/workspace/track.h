#ifndef TRACK_H
#define TRACK_H

#include <QObject>

class Track : public QObject
{
    Q_OBJECT
public:
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

   // private properties:
   // - file name
   // - loop
   // - startTime
   // - endTime
   // - fadeInDuration
   // - fadeOutDuration
    
signals:
    
public slots:
    
};

#endif // TRACK_H
