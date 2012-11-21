#ifndef TRACK_H
#define TRACK_H

#include <sstream>
#include <string>
#include <QObject>
#include "common.h"
//#include "TagLibAmalgam.h"
#include <QFileInfo>


class Track : public QObject
{

    Q_OBJECT
    //Q_PROPERTY(const QString path READ getPath)
    //Q_PROPERTY(const QString filename READ extractFilename)
    Q_PROPERTY(bool loopEnabled READ isLoopEnabled)
    Q_PROPERTY(bool showFilename READ shouldShowFilename)
    Q_PROPERTY(int startTime READ getStartTime)
    Q_PROPERTY(int endTime READ getEndTime)
    Q_PROPERTY(int fadeInDuration READ getFadeInDuration)
    Q_PROPERTY(int fadeOutDuration READ getFadeOutDuration)
    Q_PROPERTY(const QString * artist READ getArtist WRITE setArtist)
    Q_PROPERTY(const QString * title READ getTitle WRITE setTitle)
    Q_PROPERTY(int fadeOutDuration READ getFadeOutDuration)
public:
    ~Track(){
       QLOG_TRACE() << this << " deleting Track"; // << this->path << "|"
        //             << this->startTime
       //              << "-"
       //              << this->endTime
       //              << "]";
    }


    Track(const Track& track);

    Track(
        const QString &url,
        bool loop,
        int startTime, // milliseconds
        int endTime,
        int fadeInDuration,
        int fadeOutDuration,
        bool showFilename,
        QObject *parent = 0
     );
     Track(const QString &url,QObject *parent = 0);
     //Track(QObject *parent = 0);


     QString getDisplayName() const;
    QString getPath() const;
    QString getFilename() const;
    bool shouldShowFilename() const{return showFilename;}
    bool isLoopEnabled() const{return loopEnabled;}
    int getStartTime() const{return startTime;}
    int getEndTime() const{return endTime;}
    int getFadeInDuration() const{return fadeInDuration;}
    int getFadeOutDuration() const{return fadeOutDuration;}
    bool isValid() const {return fileInfo.exists();}
    //TagLib::Tag *getTag() const {return fileRef->tag();}
    static int compare(const Track &a, const Track &b);
    bool operator< (const Track &other) const;
    const QString *  getArtist() const{return &artist;}
    const QString *  getTitle() const{return &title;}
    void  setArtist(const QString * artist);
    void  setTitle(const QString * title);
    void print() const;

private:
    QFileInfo fileInfo;
    //QString path;
    //QString filename;
    bool loopEnabled;
    int startTime; // milliseconds
    int endTime;
    int fadeInDuration;
    int fadeOutDuration;
    bool showFilename;
    //TagLib::FileRef *fileRef;
    QString title;
    QString artist;
    void extractFilename(const QString & url);

signals:
    void tagUpdated();
    void tagArtistUpdate();
    void tagTitleUpdate();
    
public slots:
    
};

#endif // TRACK_H
