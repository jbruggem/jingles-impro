
#include "tracklist.h"

TrackList::TrackList(QObject *parent) : QAbstractListModel(parent) {
}


QVariant TrackList::data(const QModelIndex &index, int role)  const{
    if (role == Qt::DisplayRole)
    {
        return this->at(index.row())->getFilename();
    }
    return QVariant();
}

int TrackList::rowCount(const QModelIndex &parent) const{
    return this->length();
}

std::ostream& operator<< (std::ostream &out, const TrackList &list) {
	for (int i = 0; i < list.size(); i++){
		const Track *t = list.at(i);
		out << "\n   Track[" << t->getPath().toStdString() << "|"
							 << t->getStartTime()
							 << "-"
							 << t->getEndTime()
							 << "]";
	}
	return out;
}
