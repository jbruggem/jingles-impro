
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
#include "workspace.h"
#include <iostream>

#include "basicui.h"


int newmain(int argc, char ** argv){
    QApplication app(argc, argv);
    app.setApplicationName(QObject::tr("ImproGui"));

    QsLogging::Logger& logger  = QsLogging::Logger::instance();
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
    //TrackStock * stock = activeWorkspace->getStock();
    //TrackPlaylist * playlist = activeWorkspace->getTrackPlaylist();

    Track * t;

    t = new Track("file:///home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 01 Prenez place.mp3",false,3000,20000,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("file:///home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 10 Le vaste espace.mp3",false,1000,-1,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("file:///home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 03 Sueurs froides.mp3",false,8000,25000,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    // add some elements of the stocklist to the playlist using the workspace API
    activeWorkspace->stockToList(1);

    // give the workspace to the media player (or use the controller as a broker between them?)
    // the media player should register to the signals triggered when a track is added or remove from the playlist
    // ...

    // display stock & list
    // ...
    //QLOG_TRACE() << (* activeWorkspace);
    std::cout << "Workspace: " << * activeWorkspace <<std::endl;


    // ask the media player to start a Track
    // ...
    //new LibvlcMediaPlayer(fileName.toLocal8Bit().constData())

    BasicUi ui;
    ui.setWorkspace(activeWorkspace);
    ui.show();
    app.exec();

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

