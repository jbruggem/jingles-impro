
CONFIG += debug_and_release

TEMPLATE = app
TARGET = 
DEPENDPATH += . src src/externals/qslog
INCLUDEPATH += . src src/externals/qslog
LIBS += -lvlc

# Input
HEADERS += \
	src/avobject.h \
	src/buttonpanel.h \
#	src/improgui.h \
	src/libvlcmediaplayer.h \
	src/mainwindow.h \
	src/mediaplayerhandler.h \
	src/mediaplayerinterface.h \
	src/mediaplaylist.h \
	src/nullptr.h \
	src/pushbuttonwithextras.h \
#	src/tracklisthandler.h \
	src/externals/qslog/QsDebugOutput.h \
	src/externals/qslog/QsLog.h \
	src/externals/qslog/QsLogDest.h \
        src/workspace/workspace.h \
        src/workspace/trackstock.h \
        src/workspace/trackplaylist.h \
        src/workspace/track.h
SOURCES += \
	src/avobject.cpp \
	src/buttonpanel.cpp \
#	src/improgui.cpp \
	src/libvlcmediaplayer.cpp \
	src/main.cpp \
	src/mainwindow.cpp \
	src/mediaplayerhandler.cpp \
	src/mediaplaylist.cpp \
	src/pushbuttonwithextras.cpp \
#	src/tracklisthandler.cpp \
	src/externals/qslog/QsDebugOutput.cpp \
	src/externals/qslog/QsLog.cpp \
	src/externals/qslog/QsLogDest.cpp \
        src/workspace/workspace.cpp \
        src/workspace/trackstock.cpp \
        src/workspace/trackplaylist.cpp \
        src/workspace/track.cpp \
        src/new-main.cpp

CONFIG(debug, debug|release) {
	message("debug")
	DESTDIR = debug
	OBJECTS_DIR = debug/obj
	MOC_DIR = debug/moc
	RCC_DIR = debug/rcc
	UI_DIR = debug/ui
}
CONFIG(release, debug|release) {
	message("release")
	DESTDIR = release
	OBJECTS_DIR = release/obj
	MOC_DIR = release/moc
	RCC_DIR = release/rcc
	UI_DIR = release/ui
}

unix:!macx:!symbian: LIBS += -lX11
