
#ifndef HISTORY_H_
#define HISTORY_H_

#include <QStringList>

// todo limit number of items in history

class History {
	public:
		History();
		void    add(const QString &);
		bool    canGoBack() const;
		QString back();
		QString forward();
		QString getCurrent() const;
		void    print() const;
	private:
		QStringList backHistory;
		QStringList forwardHistory;
};

#endif
