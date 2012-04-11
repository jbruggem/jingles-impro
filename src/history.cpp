
#include "history.h"

#include "QsLog.h"
// #include <QStringList>

History::History() {
}

void History::add(const QString &path) {
	QLOG_TRACE() << "History::add()";
	forwardHistory.clear();
	backHistory.append(path);
}

bool History::canGoBack() const {
	QLOG_TRACE() << "History::canGoBack()";
	return backHistory.length() > 1;
}

QString History::back() {
	QLOG_TRACE() << "History::back()";
	if (not backHistory.isEmpty()) {
		forwardHistory.prepend(backHistory.takeLast());
	}
	return backHistory.value(backHistory.length()-1);
}

QString History::forward() {
	QLOG_TRACE() << "History::forward()";
	if (not forwardHistory.isEmpty()) {
		backHistory.append(forwardHistory.takeFirst());
	}
	return backHistory.value(backHistory.length()-1);
}

QString History::getCurrent() const {
	QLOG_TRACE() << "History::getCurrent()";
	return backHistory.value(backHistory.length()-1);
}

void History::print() const {
	QLOG_TRACE() << "History::print()";
}
