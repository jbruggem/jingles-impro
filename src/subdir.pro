
include(externals/subdir.pro)
include(qt-ui/subdir.pro)
include(workspace/subdir.pro)

currentDir = src

DEPENDPATH += \
	$${currentDir}

INCLUDEPATH += \
	$${currentDir}

HEADERS += \
	$${currentDir}/avobject.h \
	$${currentDir}/buttonpanel.h \
	$${currentDir}/history.h \
	$${currentDir}/libvlcmediaplayer.h \
	$${currentDir}/mainwindow.h \
	$${currentDir}/mediaplayerhandler.h \
	$${currentDir}/mediaplayerinterface.h \
	$${currentDir}/mediaplaylist.h \
	$${currentDir}/nullptr.h \
	$${currentDir}/pushbuttonwithextras.h \

SOURCES += \
	$${currentDir}/avobject.cpp \
	$${currentDir}/buttonpanel.cpp \
	$${currentDir}/history.cpp \
	$${currentDir}/libvlcmediaplayer.cpp \
	$${currentDir}/main.cpp \
	$${currentDir}/mainwindow.cpp \
	$${currentDir}/mediaplayerhandler.cpp \
	$${currentDir}/mediaplaylist.cpp \
	$${currentDir}/pushbuttonwithextras.cpp \
