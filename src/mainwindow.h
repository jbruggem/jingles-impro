
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

class ButtonPanel;
class QAction;
class MediaPlaylist;

class MainWindow : public QMainWindow {
	
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent = 0);
		void setPlaylist(MediaPlaylist *);
	
	private slots:
		void addTracks();
		void toggleEditMode();
		void clearPlaylist();
		void update();
	
	private:
		// Initialization functions
		void createCentralWidget();
		void createActions();
		void createSideBar();
		
		// Update functions
		void updateSideBar();
		void updateButtonPanel();
		
		// Playlist panel
		ButtonPanel *buttonPanel;
		
		// Actions
		QAction *addAction;
		QAction *editAction;
		QAction *clearAction;
		
		// SideBar
		QToolBar *sideBar;
		
		// Other members
		bool editMode;
		MediaPlaylist *playlist;
};

#endif
