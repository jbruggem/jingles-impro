#include "track.h"
#include "nullptr.h"

//xxx do we want the copy constructor to use a new fileRef or just copy the other object's pointer?
Track::Track(const Track& track):
    QObject(track.parent()),
    fileInfo(track.fileInfo),
    loopEnabled(track.loopEnabled),
    startTime(track.startTime),
    endTime(track.endTime),
    fadeInDuration(track.fadeInDuration),
    fadeOutDuration(track.fadeOutDuration) //,
    //fileRef(track.fileRef)
{
     QLOG_TRACE() << "Building Track from other track";
}
/*
Track::Track(QObject *parent) :
    QObject(parent),
    //path(),
    loopEnabled(false),
    startTime(0),
    endTime(0),
    fadeInDuration(0),
    fadeOutDuration(0),
    //fileRef(nullptr)
{
   QLOG_TRACE() << "Building Track from nothing";
}*/

Track::Track(const QString &url, bool loop, int startTime, int endTime, int fadeInDuration, int fadeOutDuration,QObject *parent) :
    QObject(parent),
    //path(url),
    loopEnabled(loop),
    startTime(startTime),
    endTime(endTime),
    fadeInDuration(fadeInDuration),
    fadeOutDuration(fadeOutDuration)
{
    QLOG_TRACE() << "Building Track with full params";
    this->extractFilename(url);
    // conversion of QString to const char * according to
    // http://qt-project.org/faq/answer/how_can_i_convert_a_qstring_to_char_and_vice_versa
    //QByteArray temp = url.toLocal8Bit();
    //fileRef = new TagLib::FileRef(temp.data());
}

Track::Track(const QString &url,QObject *parent) :
    QObject(parent),
    //path(url),
    loopEnabled(false),
    startTime(0),
    endTime(0),
    fadeInDuration(0),
    fadeOutDuration(0)
{
    QLOG_TRACE() << "Building Track from URL";
    this->extractFilename(url);
    // conversion of QString to const char * according to
    // http://qt-project.org/faq/answer/how_can_i_convert_a_qstring_to_char_and_vice_versa
    //QByteArray temp = url.toLocal8Bit();
    //fileRef = new TagLib::FileRef(temp.data());
}

void Track::extractFilename(const QString &url){
    fileInfo = new QFileInfo(url);
}

QString Track::getPath() const{
    return fileInfo->absoluteFilePath();
}
QString Track::getFilename() const{
    return fileInfo->baseName();
}

int Track::compare(const Track &a, const Track &b) {
    int returnValue = QString::localeAwareCompare(a.fileInfo->canonicalFilePath(), b.fileInfo->canonicalFilePath());
	// if the strings are different, we stop the comparison
	if (returnValue) {return returnValue;}

	returnValue = a.startTime - b.startTime;
	// if the times are different, we stop the comparison
	if (returnValue) {return returnValue;}

	returnValue = a.endTime - b.endTime;
	if (returnValue) {return returnValue;}

	returnValue = a.fadeInDuration - b.fadeInDuration;
	if (returnValue) {return returnValue;}

	returnValue = a.fadeOutDuration - b.fadeOutDuration;
	if (returnValue) {return returnValue;}

	returnValue = a.loopEnabled - b.loopEnabled;
	if (returnValue) {return returnValue;}

	// additional checks can be added here

	return 0;
}

bool Track::operator<(const Track &other) const {
	return compare(*this, other) < 0;
}

void  Track::setArtist(const QString * artist) {
    QLOG_TRACE() << "Track's artist updated.";
    this->artist = *artist;
    emit tagUpdated();
    emit tagArtistUpdate();
}
void  Track::setTitle(const QString * title) {
    QLOG_TRACE() << "Track's title updated.";
    this->title = *title;
    emit tagUpdated();
    emit tagTitleUpdate();
}

void Track::print() const {
	QLOG_INFO() << "Track::print()";
    QLOG_INFO() << "path:           " << this->getPath();
	QLOG_INFO() << "startTime:      " << startTime;
	QLOG_INFO() << "endTime:        " << endTime;
	QLOG_INFO() << "fadeInDuration: " << fadeInDuration;
	QLOG_INFO() << "fadeOutDuration:" << fadeOutDuration;
	QLOG_INFO() << "loopEnabled:    " << loopEnabled;
    //QLOG_INFO() << "isValid?:       " << isValid();
}
