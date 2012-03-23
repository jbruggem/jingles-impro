
// -----------old main
#include <QApplication>
#include <QDir>
#include "QsLog.h"
#include "QsLogDest.h"
#include "mainwindow.h"


#include "testui.h"

#ifdef Q_WS_X11
    #include <X11/Xlib.h>
#endif

#include "workspace.h"
#include "basicui.h"


int main(int argc, char ** argv){
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

    Track * t;

    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 01 Prenez place.mp3",false,3000,20000,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 10 Le vaste espace.mp3",false,1000,-1,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 03 Sueurs froides.mp3",false,8000,25000,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("res/one.mp3",false,0,-1,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("res/two.mp3",false,0,-1,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("res/three.mp3",false,0,-1,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    // add some elements of the stocklist to the playlist using the workspace API
    activeWorkspace->stockToList(0);
    activeWorkspace->stockToList(1);
    activeWorkspace->stockToList(2);
    activeWorkspace->stockToList(3);
    activeWorkspace->stockToList(4);
    activeWorkspace->stockToList(5);

    // give the workspace to the media player (or use the controller as a broker between them?)
    // the media player should register to the signals triggered when a track is added or remove from the playlist
    // ...


    BasicUi ui;
    ui.setWorkspace(activeWorkspace);
//    TestUi ui;
    ui.show();
    app.exec();

    delete activeWorkspace;
    delete mediaPlayerFactory;
    QLOG_TRACE() << "Workspace deleted";

    return 0;
}


