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



    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 10 Le vaste espace.mp3",false,20000,30000,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 01 Prenez place.mp3",false,1000,-1,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    t = new Track("/home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 03 Sueurs froides.mp3",false,8000,25000,0,0,activeWorkspace);
    activeWorkspace->addTrack(t);

    // 01 - Dvorak - 01. Cello Concerto No.2 - Allegro.mp3

    // add some elements of the stocklist to the playlist using the workspace API
    activeWorkspace->stockToList(0);
    activeWorkspace->stockToList(2);

    // give the workspace to the media player (or use the controller as a broker between them?)
    // the media player should register to the signals triggered when a track is added or remove from the playlist
    // ...

    // display stock & list
    //QLOG_TRACE() << (* activeWorkspace);
    std::cout << "Workspace: " << * activeWorkspace <<std::endl;


    // ask the media player to start a Track
    t = activeWorkspace->getPlaylist()->getTrack(0);
    MediaPlayerFactory * mediaPlayerFactory = new GstMediaPlayerFactory();

    Players * players = new Players(mediaPlayerFactory);

    int p1 = players->createPlayer(activeWorkspace->getPlaylist()->getTrack(0));
    //int p2 = players->createPlayer(activeWorkspace->getPlaylist()->getTrack(1));

//    GstPlayer * player = new GstPlayer();
//    player->load(t);
    //sleep(2);

    sleep(2);
    QLOG_INFO() << "In main.Running play.";
       players->getPlayer(p1)->play();
    sleep(1);

    //QLOG_INFO() << "PLAY 2!";
    //  players->getPlayer(p2)->play();

    QLOG_TRACE() << "What do we have?";
    QLOG_TRACE() << "Track 0: "<<
                    *activeWorkspace->getPlaylist()->getTrack(0)->getArtist()
                 << " - "<<
                    *activeWorkspace->getPlaylist()->getTrack(0)->getTitle();
    QLOG_TRACE() << "Track 1: "<<
                    *activeWorkspace->getPlaylist()->getTrack(1)->getArtist()
                 << " - "<<
                    *activeWorkspace->getPlaylist()->getTrack(1)->getTitle();
    sleep(10);

    //QLOG_INFO() << "PLAY 2!";
    //  players->getPlayer(p2)->play();
    sleep(30);

    players->stopAll();

    delete players;
    delete mediaPlayerFactory;
    delete activeWorkspace;
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

/*


-
-    QLOG_TRACE() << "Gst init";
-   QtConcurrent::run(&initialiseGstreamer);
-
-    QLOG_TRACE() << "Start playthread";
-    PlayThread * pt = new PlayThread();
-
-    gst_stream_volume_set_volume(GST_STREAM_VOLUME(pt->getPipeline()),GST_STREAM_VOLUME_FORMAT_LINEAR,1.0);
-
-
-    pt->start();
-
-
-    gint64 pos =  30 * GST_SECOND;
-
-    sleep(5);
-
-    QLOG_TRACE() << "seek";
-    gst_element_seek_simple(pt->pipeline,GST_FORMAT_TIME,GST_SEEK_FLAG_ACCURATE,pos);
-
-    QLOG_TRACE() << "In main thread. Sleep 2.";
-    //pt.pipeline;
-
-
-    sleep(5);
-
-
-    gint64 position = 0;
-    GstFormat format = GST_FORMAT_TIME;
-    bool ok = gst_element_query_position(pt->getPipeline(),&format,&position);
-
-
-    QLOG_TRACE() << "Query position:" << ok;
-    QLOG_TRACE() << "Position value in ms:" << (position/GST_MSECOND);
-
-    pos =  230 * GST_SECOND;
-    gst_element_seek_simple(pt->pipeline,format,GST_SEEK_FLAG_FLUSH,pos);
-
-
-    gdouble volume, incvolume = 0.05;
-    //volume = gst_stream_volume_get_volume(GST_STREAM_VOLUME(pt->getPipeline()),GST_STREAM_VOLUME_FORMAT_LINEAR);
-    volume = 1;
-
-    for(;volume > 0.0;volume-=incvolume){
-        QLOG_TRACE() << "Volume:" << gst_stream_volume_get_volume(GST_STREAM_VOLUME(pt->getPipeline()),GST_STREAM_VOLUME_FORMAT_LINEAR);
-        usleep(500*1000);
-        gst_stream_volume_set_volume(GST_STREAM_VOLUME(pt->getPipeline()),GST_STREAM_VOLUME_FORMAT_LINEAR,volume);
-}
-
-
-    sleep(60);
-
-    QLOG_TRACE() << "Exit.";
-    //oldmain(argc, argv);
-    return 0;
-}
-
  */
