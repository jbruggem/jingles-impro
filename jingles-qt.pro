
CONFIG += debug_and_release

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
LIBS += -lvlc

include(subdir.pro)

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
