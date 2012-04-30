
#ifndef TESTUI_H_
#define TESTUI_H_

#include <QWidget>
#include <QList>

class QTreeView;
class QStandardItemModel;

class Item {
	public:
		enum SortingMode {
			SortById1,
			SortById2,
		};
		Item(const QString &id1, const QString &id2, const QString &id3);
		QString id1;
		QString id2;
		QString id3;
};

class TestUi : public QWidget {
	public:
		TestUi(QWidget *parent = 0);
		void setSortingMode(Item::SortingMode);
		void refresh();
	private:
		QList<Item>         l;
		QTreeView          *v;
		QStandardItemModel *m;
		Item::SortingMode sortingMode;
};

#endif
