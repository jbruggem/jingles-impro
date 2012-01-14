
#ifndef MEDIAPLAYLIST_H
#define MEDIAPLAYLIST_H

#include <QStringList>

class MediaPlaylist : public QStringList {
	public:
		MediaPlaylist();
		void print() const;
};

#endif
