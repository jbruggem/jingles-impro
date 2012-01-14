
#include "mediaplaylist.h"

#include <QStringList>
#include "QsLog.h"

MediaPlaylist::MediaPlaylist() {
}

void MediaPlaylist::print() const {
	for (int32_t i = 0; i < this->length(); i++) {
		QLOG_INFO() << '\t' << i << " | " << this->at(i);
	}
}
