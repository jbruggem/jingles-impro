
currentDir = src/externals/qslog

DEPENDPATH += \
	$${currentDir}

INCLUDEPATH += \
	$${currentDir}

HEADERS += \
	$${currentDir}/QsDebugOutput.h \
	$${currentDir}/QsLog.h \
	$${currentDir}/QsLogDest.h

SOURCES += \
	$${currentDir}/QsDebugOutput.cpp \
	$${currentDir}/QsLog.cpp \
	$${currentDir}/QsLogDest.cpp
