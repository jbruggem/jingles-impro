#include "workspace/workspace.h"



// this is just a draft


// manually set some file paths for scaffholding
// load it in the workspace using the workspace API
// with the appropriate settings for all the Track properties
Workspace activeWorkspace = Workspace(0);

Track * t;

t = new Track("file:///home/jehan/Perso/m/Doctor FLAKE/Paradis Dirtyficiels/Doctor FLAKE - Paradis Dirtyficiels - 01 Prenez place.mp3",false,30,200,0,0,activeWorkspace);

TrackStock * stock = activeWorkspace.getStock();

stock->add(t);


// add some elements of the stocklist to the playlist using the workspace API
















//*/
