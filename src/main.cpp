
// -----------old main
#include <QApplication>
#include <QDir>
#include "QsLog.h"
#include "QsLogDest.h"
#include "mainwindow.h"
#include "testui.h"
#include "gstplayer.h"
#include "players.h"
#include "gstmediaplayerfactory.h"

#ifdef Q_WS_X11
    #include <X11/Xlib.h>
#endif

#include "workspace.h"
#include "basicui.h"
#include "uicontroller.h"

/****
  Let's start listing coders & helping hands

  devs:
  Alexandre D'Erman
  Jehan Bruggeman

  Contributors:
  Gary Verhaegen

  Testers:
  Michaël Waumans
  Nastassia Gumuchdjian

****/


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

    // scaffholding
    // load file list from ".txt"
    // this is temporary
    QFile file("./filestoload.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QLOG_ERROR() << file.errorString();
        return 1;
    }

    QLOG_TRACE() << "Loading file " << file.fileName() ;
    QTextStream in(&file);
    int index=0;
    while(!in.atEnd()) {
        QString line = in.readLine();
        QLOG_TRACE() << "Reading line: " << line ;
        QStringList fields = line.split(",");
        if(fields.size() < 8 ){
            QLOG_TRACE() << "Line unreadable";
        }else{
            t = new Track(
                        fields[0], // file name
                        ("true" == fields[1].toLower()), // loop
                        fields[2].toInt(), // start
                        fields[3].toInt(), // stop
                        fields[4].toInt(), // fade in
                        fields[5].toInt(), // fade out
                        ("true" == fields[6].toLower()), // showFilename
                        activeWorkspace
                        );

            index = activeWorkspace->addTrack(t);
            if( ("b" == fields[7].toLower()) ){
                activeWorkspace->stockToButtons(index);
            }else{
                activeWorkspace->stockToList(index);
            }
        };
    }


    // give the workspace to the media player (or use the controller as a broker between them?)
    // the media player should register to the signals triggered when a track is added or remove from the playlist
    // ...

    // create a "Players" object to deal with controlling the players
    MediaPlayerFactory * mediaPlayerFactory = new GstMediaPlayerFactory();
    Players * players = new Players(mediaPlayerFactory);
    UiController controller(players,activeWorkspace);

    BasicUi ui(&controller);
    ui.setWorkspace(activeWorkspace);

//    TestUi ui;
    ui.show();
    app.exec();

    delete activeWorkspace;
    //delete player;
    QLOG_TRACE() << "Workspace deleted";

    return 0;
}
