
currentDir = src/workspace

DEPENDPATH += \
	$${currentDir}
INCLUDEPATH += \
	$${currentDir}

HEADERS += \
	$${currentDir}/workspace.h \
	$${currentDir}/trackstock.h \
	$${currentDir}/trackplaylist.h \
	$${currentDir}/track.h \
	$${currentDir}/common.h \
	$${currentDir}/trackcollection.h \
	$${currentDir}/tracklist.h

SOURCES += \
	$${currentDir}/workspace.cpp \
	$${currentDir}/trackstock.cpp \
	$${currentDir}/trackplaylist.cpp \
	$${currentDir}/track.cpp \
	$${currentDir}/trackcollection.cpp \
	$${currentDir}/tracklist.cpp
