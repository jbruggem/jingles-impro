
#include <QApplication>
#include <QDir>
#include "QsLog.h"
#include "QsLogDest.h"
#include "mainwindow.h"
#include "mediaplaylist.h"
#include "mediaplayerhandler.h"

#ifdef Q_WS_X11
	#include <X11/Xlib.h>
#endif

int main(int argc, char **argv) {
	
	#ifdef Q_WS_X11
		XInitThreads();
	#endif
	
	QApplication app(argc, argv);
	app.setApplicationName(QObject::tr("ImproGui"));

	// Initialise the logging module
	QsLogging::Logger& logger = QsLogging::Logger::instance();
	logger.setLoggingLevel(QsLogging::TraceLevel);
	const QString sLogPath(QDir(app.applicationDirPath()).filePath("log.txt"));
	QsLogging::DestinationPtr fileDestination( QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
	QsLogging::DestinationPtr debugDestination( QsLogging::DestinationFactory::MakeDebugOutputDestination() );
	logger.addDestination(debugDestination.get());
	logger.addDestination(fileDestination.get());
	
	MediaPlaylist playlist;
	playlist.append("res/one.mp3");
	playlist.append("res/two.mp3");
	playlist.append("res/three.mp3");
	
	MediaPlayerHandler mph;
	
	MainWindow mw;
	mw.setPlaylist(&playlist);
	mw.setMediaPlayer(&mph);
	
	mw.show();

	return app.exec();
}
