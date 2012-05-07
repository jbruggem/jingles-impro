#include "gstmediaplayerfactory.h"
#include "workspace.h"
#include "QsLog.h"
#include "QsLogDest.h"
#include <QApplication>
#include <QDir>

//#include <gst/gst.h>
//#include <gst/interfaces/streamvolume.h>
//#include <iostream>
//#include "maintests.h"
//#include "mediaplaylist.h"
//#include "mediaplayerhandler.h"
//#include "gstplayer.h"
#include "players.h"



void realmain(){
    QLOG_TRACE() << "Testing media player";


    // manually set some file paths for scaffolding
    // load it in the workspace using the workspace API
    // with the appropriate settings for all the Track properties
    Workspace * activeWorkspace = new Workspace(0);
    //TrackStock * stock = activeWorkspace->getStock();
    //TrackPlaylist * playlist = activeWorkspace->getTrackPlaylist();

    Track * t;



    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 01 Prenez place.mp3",false,3000,20000,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 10 Le vaste espace.mp3",false,1000,-1,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 03 Sueurs froides.mp3",false,8000,25000,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    // 01 - Dvorak - 01. Cello Concerto No.2 - Allegro.mp3

    // add some elements of the stocklist to the playlist using the workspace API
    activeWorkspace->stockToList(1);
    activeWorkspace->stockToList(2);

    // give the workspace to the media player (or use the controller as a broker between them?)
    // the media player should register to the signals triggered when a track is added or remove from the playlist
    // ...

    // display stock & list
    // ...
    //QLOG_TRACE() << (* activeWorkspace);
    std::cout << "Workspace: " << * activeWorkspace <<std::endl;


    // ask the media player to start a Track
    // ...
    t = activeWorkspace->getPlaylist()->getTrack(0);
    MediaPlayerFactory * mediaPlayerFactory = new GstMediaPlayerFactory();
    /*Players pwrapper(mediaPlayerFactory);*/

    Players * players = new Players(mediaPlayerFactory);

    int p1 = players->createPlayer(activeWorkspace->getPlaylist()->getTrack(0));
    int p2 = players->createPlayer(activeWorkspace->getPlaylist()->getTrack(1));

//    GstPlayer * player = new GstPlayer();
//    player->load(t);
    //sleep(2);

    QLOG_INFO() << "PLAY!";
    //player->play();
    //   players->getPlayer(p1)->play();
    sleep(5);

//    GstPlayer * player2 = new GstPlayer();
//    player2->load(activeWorkspace->getPlaylist()->getTrack(1));
    QLOG_INFO() << "PLAY 2!";
    //  players->getPlayer(p2)->play();

    sleep(30);
    //pwrapper.play(t);
    //sleep(2);
    //player->stop();
    //player2->stop();
    players->stopAll();
    //new LibvlcMediaPlayer(fileName.toLocal8Bit().constData())

    delete players;
    delete mediaPlayerFactory;
    delete activeWorkspace;
    //delete player;
    QLOG_TRACE() << "Workspace deleted";


}



int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setApplicationName(QObject::tr("ImproGui"));

    QsLogging::Logger& logger  = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath(QDir(app.applicationDirPath()).filePath("log.txt"));
    QsLogging::DestinationPtr fileDestination( QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    QsLogging::DestinationPtr debugDestination( QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    realmain();
}
