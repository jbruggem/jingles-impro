jingles-impro
=============

A niche application to help "the music guy" during improv games. It will load buttons on the left part of the screen (for short jingles/loops) and a playlist on the right (for transitions between impros).


Building the jingles-impro project
-------------------------------

This project needs:
- g++
- libgstreamer0.10-dev
- libqt4-dev



To generate the directory structure and the makefiles for the build:

      $ qmake

To compile in release mode:

      $ make

To compile in debug mode:

	    $ make debug

To compile in both debug and release modes:

	    $ make all

To compile several files in parallel, use the "-j" flag:

	    $ make -j4 all

To make compilation even (much) faster, install and use ccache:

	    $ sudo apt-get install ccache
	    $ make -j4 CXX="ccache g++" all

To run the generated executables:

	    $ ./release/jingles-qt
	    $ ./debug/jingles-qt


Using the jingles-impro project
-------------------------------

Since we haven't finished yet the UI to create your playlists, you write your config to `filestoload.txt`. 
Syntax is the following:

        file path,shouldLoop,start,end,fadeIn,fadeOut,showFileName,buttonOrList

* `file path`: currently no escaping: files with "," in them will not be properly loaded
* `shouldLoop`: boolean
* `start`: time in ms
* `end`: time in ms or -1 if track should be played to the end
* `fadeIn/fadeOut`: [not implemented] time in ms
* `showFileName`: boolean (`true` or `false`). Should the UI show the filename or the id3 'title' tag?
* `buttonOrList`: 'b' to show in the buttons, 'p' to show in the list 

