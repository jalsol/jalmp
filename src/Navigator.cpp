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

	for (int i = 0; i < parts.size(); ++i) {
		QString part = parts.at(i);
		if (part == "playlist") {
			playlistId = parts.at(++i).toLongLong();
		} else if (part == "artist") {
			artistId = parts.at(++i).toLongLong();
		} else if (part == "track") {
			trackId = parts.at(++i).toLongLong();
		} else if (part == "like") {
			like = true;
		} else if (part == "unlike") {
			like = false;
		}
	}

	if (like != -1) {
		emit toggledFavorite(trackId, like);
	} else if (artistId != ArtistId::Invalid) {
		emit navigatedToArtist(artistId);
	} else if (trackId != TrackId::Invalid) {
		emit navigatedToTrack(playlistId, trackId);
	} else if (playlistId != PlaylistId::Invalid) {
		emit navigatedToPlaylist(playlistId);
	}
}
