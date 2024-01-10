#include "Navigator.hpp"

#include <QDebug>
#include <QStringList>

Navigator* Navigator::instance() {
	static Navigator* instance = new Navigator();
	return instance;
}

void Navigator::navigateTo(QString path) {
	qDebug() << "navigating:" << path;
	QStringList parts = path.split('/');
	parts.removeAll("");

	PlaylistId playlistId = PlaylistId::Invalid;
	ArtistId artistId = ArtistId::Invalid;
	TrackId trackId = TrackId::Invalid;
	int like = -1;
	int queue = -1;
	int queueTypeInt = -1;

	for (int i = 0; i < parts.size(); ++i) {
		QString part = parts.at(i);
		if (part == "playlist") {
			playlistId = parts.at(++i).toLongLong();
		} else if (part == "artist") {
			artistId = parts.at(++i).toLongLong();
		} else if (part == "track") {
			trackId = parts.at(++i).toLongLong();
		} else if (part == "queue_delete") {
			trackId = parts.at(++i).toLongLong();
			queueTypeInt = parts.at(++i).toInt();
			queue = 0;
		} else if (part == "queue_add") {
			trackId = parts.at(++i).toLongLong();
			queue = 1;
		} else if (part == "queue_up") {
			trackId = parts.at(++i).toLongLong();
			queueTypeInt = parts.at(++i).toInt();
			queue = 2;
		} else if (part == "queue_down") {
			trackId = parts.at(++i).toLongLong();
			queueTypeInt = parts.at(++i).toInt();
			queue = 3;
		} else if (part == "like") {
			like = true;
		} else if (part == "unlike") {
			like = false;
		}
	}

	if (like != -1) {
		emit toggledFavorite(trackId, like);
	} else if (queue != -1) {
		QueueType queueType = static_cast<QueueType>(queueTypeInt);

		switch (queue) {
		case 0:
			emit queueDeleted(queueType, trackId);
			break;
		case 1:
			emit queueAdded(trackId);
			break;
		case 2:
			emit queueUp(queueType, trackId);
			break;
		case 3:
			emit queueDown(queueType, trackId);
			break;
		}
	} else if (artistId != ArtistId::Invalid) {
		emit navigatedToArtist(artistId);
	} else if (trackId != TrackId::Invalid) {
		emit navigatedToTrack(playlistId, trackId);
	} else if (playlistId > 0) {
		emit navigatedToPlaylist(playlistId);
	} else if (playlistId == PlaylistId::Favorites) {
		emit navigatedToHome();
	} else if (playlistId == PlaylistId::UserQueue) {
		emit navigatedToHome();
	} else {
		emit navigatedToSearch();
	}
}
