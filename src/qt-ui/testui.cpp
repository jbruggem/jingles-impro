
#include "testui.h"

#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>

TestUi::TestUi(QWidget *parent)
	: QWidget (parent) {

	sortingMode = Item::SortById2;

	l << Item("a", "a", "1")
	  << Item("a", "b", "2")
	  << Item("a", "c", "3");

	v = new QTreeView;
	m = new QStandardItemModel;
	v->setModel(m);
	v->setHeaderHidden(true);
	setLayout(new QVBoxLayout);
	layout()->addWidget(v);
	refresh();
}

void TestUi::refresh() {
	m->clear();

	QMap<QString, QMap<QString, int> > map;

	switch(sortingMode) {
		case Item::SortById1:
			foreach(Item i, l) {
				if (not map[i.id1].contains(i.id3)) {
					map[i.id1][i.id3] = 1;
				} else {
					map[i.id1][i.id3]++;
				}
			}
			break;
		case Item::SortById2:
			foreach(Item i, l) {
				if (not map[i.id2].contains(i.id3)) {
					map[i.id2][i.id3] = 1;
				} else {
					map[i.id2][i.id3]++;
				}
			}
			break;
	}

	// populate the model
	foreach(QString key, map.keys()) {
		QStandardItem *parent = new QStandardItem(key);
		m->appendRow(parent);

		foreach(QString value, map[key].keys()) {
			for (int i = 0; i < map[key][value]; i++) {
				parent->appendRow(new QStandardItem(value));
			}
		}
	}

}

Item::Item(const QString &id1, const QString &id2, const QString &id3)
	: id1(id1),
	  id2(id2),
	  id3(id3) {
}
