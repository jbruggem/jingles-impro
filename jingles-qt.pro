
CONFIG += debug_and_release

TEMPLATE = app
TARGET = 

DEPENDPATH  += . src src/player  src/player/gst src/workspace \
 src/externals/qslog src/externals/taglib src/qt-ui
INCLUDEPATH += . src src/player  src/player/gst src/workspace \
 src/externals/qslog src/externals/taglib src/qt-ui



# Input
HEADERS += \
    src/externals/qslog/QsDebugOutput.h \
    src/externals/qslog/QsLog.h \
    src/externals/qslog/QsLogDest.h \
    src/workspace/workspace.h \
    src/workspace/trackstock.h \
    src/workspace/trackplaylist.h \
    src/workspace/tracklist.h \
    src/workspace/track.h \
    src/workspace/trackcollection.h \
    src/player/mediaplayerfactory.h \
    src/common.h \
    src/maintests.h \
    src/player/players.h \
    src/player/gst/gstplayer.h \
    src/player/gst/gstmediaplayerfactory.h \
    src/player/imediaplayer.h \
    src/qt-ui/twopaneexplorer.h \
    src/qt-ui/tracklisttreemodel.h \
    src/qt-ui/tracklisttreeview.h \
    src/qt-ui/testui.h \
    src/qt-ui/playwidgetentry.h \
    src/qt-ui/playwidget.h \
    src/qt-ui/mainwidget.h \
    src/qt-ui/editwidget.h \
    src/qt-ui/basicui.h \
    src/qt-ui/autoscrollarea.h \
    src/history.h \
    src/playwidgetentrycontroller.h \
    src/uicontroller.h

SOURCES += \
    src/externals/qslog/QsDebugOutput.cpp \
    src/externals/qslog/QsLog.cpp \
    src/externals/qslog/QsLogDest.cpp \
    src/workspace/workspace.cpp \
    src/workspace/trackstock.cpp \
    src/workspace/tracklist.cpp \
    src/workspace/trackplaylist.cpp \
    src/workspace/track.cpp \
    src/workspace/trackcollection.cpp \
    src/player/players.cpp \
    src/player/gst/gstplayer.cpp \
    src/player/gst/gstmediaplayerfactory.cpp \
    src/main.cpp \
    src/qt-ui/twopaneexplorer.cpp \
    src/qt-ui/tracklisttreemodel.cpp \
    src/qt-ui/tracklisttreeview.cpp \
    src/qt-ui/testui.cpp \
    src/qt-ui/playwidgetentry.cpp \
    src/qt-ui/playwidget.cpp \
    src/qt-ui/mainwidget.cpp \
    src/qt-ui/editwidget.cpp \
    src/qt-ui/basicui.cpp \
    src/qt-ui/autoscrollarea.cpp \
    src/history.cpp \
    src/playwidgetentrycontroller.cpp \
    src/uicontroller.cpp


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

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += gstreamer-0.10 gstreamer-plugins-base-0.10 gstreamer-base-0.10 gstreamer-interfaces-0.10

QMAKE_CXXFLAGS += -std=gnu++0x
