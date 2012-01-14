
#include <QApplication>
#include <QDir>
#include <vlc/vlc.h>
#include "QsLog.h"
#include "QsLogDest.h"
#include "mediaplaylist.h"
#include "libvlcmediaplayer.h"
#include "mediaplayerinterface.h"
#include "mediaplayerhandler.h"
// #include "improgui.h"
// #include "tracklisthandler.h"
#include "nullptr.h"

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
	logger.setLoggingLevel(QsLogging::InfoLevel);
	const QString sLogPath(QDir(app.applicationDirPath()).filePath("log.txt"));
	QsLogging::DestinationPtr fileDestination( QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
	QsLogging::DestinationPtr debugDestination( QsLogging::DestinationFactory::MakeDebugOutputDestination() );
	logger.addDestination(debugDestination.get());
	logger.addDestination(fileDestination.get());
	
	// Testing MediaPlaylist
	MediaPlaylist playlist;
	playlist.append("res/one.mp3");
	playlist.append("res/two.mp3");
	playlist.append("res/three.mp3");
	playlist.print();
	
	// Testing LibvlcMediaPlayer and MediaPlayerInterface
	// MediaPlayerInterface *mpi = new LibvlcMediaPlayer;
	// mpi->print();
	// mpi->setFileName(playlist.at(0).toLocal8Bit().constData());
	// mpi->print();
	// mpi->play();
	// mpi->print();
	// sleep(2);
	// delete mpi;
	// sleep(2);
	// mpi->pause();
	// mpi->print();
	// sleep(2);
	// mpi->play();
	// mpi->print();
	// sleep(2);
	// mpi->stop();
	// mpi->print();
	
	// Testing MediaPlayerHandler
	MediaPlayerHandler mph;
	mph.print();
	
	mph.play(playlist.at(0));
	mph.print();
	sleep(3);
	mph.play(playlist.at(1));
	mph.print();
	sleep(3);
	// mph.play(playlist.at(1));
	// sleep(3);
	// mph.play(playlist.at(1));
	// sleep(3);
	mph.stop(playlist.at(1));
	// mph.stop();
	mph.print();
	// sleep(30);
	// mph.print();
	// mph.play(playlist.at(2));
	// mph.print();
	sleep(3);
	
	// QMultiMap<QString, LibvlcMediaPlayer> mpMap;
	// mpMap.insert(playlist.at(0), playlist.at(0).toLocal8Bit().constData());
	// sleep(3);
	// mpMap.values(playlist.at(0)).last().print();
	
	// TrackListHandler tlh;
	
	// ImproGui improGui;
	// improGui.linkTo(&tlh);
	// improGui.show();

	// return app.exec();
}
