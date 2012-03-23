
// -----------old main
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


// -----------new main
#include "workspace/workspace.h"




int newmain(int argc, char ** argv){
    QApplication app(argc, argv);
    app.setApplicationName(QObject::tr("ImproGui"));

    // this is just a draft
    // Initialise the logging module
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath(QDir(app.applicationDirPath()).filePath("log.txt"));
    QsLogging::DestinationPtr fileDestination( QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    QsLogging::DestinationPtr debugDestination( QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());


    QLOG_TRACE() << "Logging initiated";

    // manually set some file paths for scaffolding
    // load it in the workspace using the workspace API
    // with the appropriate settings for all the Track properties
    Workspace * activeWorkspace = new Workspace(0);

    Track * t;

    t = new Track("file:///home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 01 Prenez place.mp3",false,30,200,0,0,activeWorkspace);

    TrackStock * stock = activeWorkspace->getStock();

    stock->add(t);


    // add some elements of the stocklist to the playlist using the workspace API

    delete activeWorkspace;
    QLOG_TRACE() << "Workspace deleted";

    return 0;
}



int oldmain(int argc, char **argv) {

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




int main(int argc, char **argv) {
    //oldmain(argc, argv);
    newmain(argc,argv);
}

