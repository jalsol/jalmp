#include "Navigator.hpp"

#include <QStringList>

Navigator* Navigator::instance() {
	static Navigator* instance = new Navigator();
	return instance;
}

void Navigator::navigateTo(QString path) {
	QStringList parts = path.split('/');
	parts.removeAll("");

	PlaylistId playlistId = PlaylistId::Invalid;
	ArtistId artistId = ArtistId::Invalid;
	TrackId trackId = TrackId::Invalid;

	for (int i = 0; i < parts.size(); ++i) {
		QString part = parts.at(i);
		if (part == "playlist") {
			playlistId = parts.at(++i).toLongLong();
		} else if (part == "artist") {
			artistId = parts.at(++i).toLongLong();
		} else if (part == "track") {
			trackId = parts.at(++i).toLongLong();
		}
	}

	if (artistId != ArtistId::Invalid) {
		emit navigatedToArtist(artistId);
	} else if (trackId != TrackId::Invalid) {
		emit navigatedToTrack(playlistId, trackId);
	} else if (playlistId != PlaylistId::Invalid) {
		emit navigatedToPlaylist(playlistId);
	}
}
