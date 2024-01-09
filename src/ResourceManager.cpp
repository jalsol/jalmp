#include "ResourceManager.hpp"

#include "ArtistBuilder.hpp"
#include "PlaylistBuilder.hpp"
#include "TrackBuilder.hpp"

#include <fstream>

ResourceManager::ResourceManager() {
	std::ifstream file("../../config.txt");
	std::string input;

	mDatabase = QSqlDatabase::addDatabase("QMARIADB");
	mDatabase.setHostName("localhost");
	mDatabase.setPort(3306);
	mDatabase.setDatabaseName("jalmp");
	mDatabase.setUserName("root");

	file >> input;
	mDatabase.setPassword(input.c_str());

	Q_ASSERT(mDatabase.open());
}

ResourceManager::~ResourceManager() { mDatabase.close(); }

ResourceManager& ResourceManager::instance() {
	static ResourceManager instance;
	return instance;
}

Artist* ResourceManager::getArtist(ArtistId id) {
	for (auto& artist : mArtists) {
		if (artist.id() == id) {
			return &artist;
		}
	}

	QSqlQuery query(mDatabase);
	query.prepare("SELECT name, cover_url FROM artist WHERE id = :id");
	query.bindValue(":id", static_cast<qlonglong>(id));

	if (!query.exec()) {
		return nullptr;
	}

	if (query.next()) {
		QString name = query.value(0).toString();
		QString cover = query.value(1).toString();

		Artist artist = ArtistBuilder()
							.setId(id)
							.setName(name)
							.setCover(cover)
							.build();
		mArtists.push_back(artist);

		return &mArtists.back();
	} else {
		return nullptr;
	}
}

Track* ResourceManager::getTrack(TrackId id) {
	for (auto& track : mTracks) {
		if (track.id() == id) {
			return &track;
		}
	}

	QSqlQuery query(mDatabase);
	query.prepare(
		"SELECT title, duration, cover_url, url FROM track WHERE id = :id");
	query.bindValue(":id", static_cast<qlonglong>(id));

	if (!query.exec()) {
		qDebug() << "exec failed\n";
		return nullptr;
	}

	if (query.next()) {
		QString title = query.value(0).toString();
		QTime duration =
			QTime::fromMSecsSinceStartOfDay(query.value(1).toInt());
		QString cover = query.value(2).toString();
		QString url = query.value(3).toString();

		Track track = TrackBuilder()
						  .setId(id)
						  .setName(title)
						  .setDuration(duration)
						  .setCover(cover)
						  .setUrl(url)
						  .build();

		mTracks.push_back(track);

		return &mTracks.back();
	} else {
		qDebug() << "empty result\n";
		return nullptr;
	}
}

Playlist* ResourceManager::getPlaylist(PlaylistId id) {
	for (auto& playlist : mPlaylists) {
		if (playlist.id() == id) {
			return &playlist;
		}
	}

	QSqlQuery query(mDatabase);
	query.prepare("SELECT name, cover_url FROM playlist WHERE id = :id");
	query.bindValue(":id", static_cast<qlonglong>(id));

	if (!query.exec()) {
		return nullptr;
	}

	if (query.next()) {
		QString name = query.value(0).toString();
		QString cover = query.value(1).toString();

		Playlist playlist =
			PlaylistBuilder().setId(id).setName(name).setCover(cover).build();
		mPlaylists.push_back(playlist);

		return &mPlaylists.back();
	} else {
		return nullptr;
	}
}

QList<Track*> ResourceManager::getTracksByPlaylist(PlaylistId playlistId) {
	QSqlQuery query(mDatabase);
	query.prepare("SELECT track_id FROM playlist_track "
				  "WHERE playlist_id = :id "
				  "ORDER BY track_priority ASC");
	query.bindValue(":id", static_cast<qlonglong>(playlistId));

	QList<Track*> result;

	if (query.exec()) {
		while (query.next()) {
			TrackId id = query.value(0).toULongLong();
			result.append(getTrack(id));
		}
	}

	return result;
}

QList<Track*> ResourceManager::getTracksByArtist(ArtistId artistId) {
	QSqlQuery query(mDatabase);
	query.prepare("SELECT a_t.track_id "
				  "FROM artist_track a_t LEFT JOIN artist a "
				  "ON a_t.artist_id = a.id "
				  "WHERE a.id = :id");
	query.bindValue(":id", static_cast<qlonglong>(artistId));

	QList<Track*> result;

	if (query.exec()) {
		while (query.next()) {
			TrackId id = query.value(0).toULongLong();
			result.append(getTrack(id));
		}
	}

	return result;
}

QList<Artist*> ResourceManager::getArtistsByTrack(TrackId trackId) {
	QSqlQuery query(mDatabase);
	query.prepare("SELECT artist_id FROM artist_track "
				  "WHERE track_id = :track_id "
				  "ORDER BY artist_priority ASC");
	query.bindValue(":track_id", static_cast<qlonglong>(trackId));

	QList<Artist*> result;

	if (query.exec()) {
		while (query.next()) {
			ArtistId id = query.value(0).toULongLong();
			result.append(getArtist(id));
		}
	}

	return result;
}

QList<Entity*> ResourceManager::getEntitiesByKeyword(const QString& keyword) {
	QSqlQuery query(mDatabase);
	QList<Entity*> result;

	// get artists
	query.prepare("SELECT id FROM artist WHERE name LIKE :keyword LIMIT 20");
	query.bindValue(":keyword", QString("%%1%").arg(keyword));

	if (query.exec()) {
		while (query.next()) {
			ArtistId id = query.value(0).toULongLong();
			result.append(getArtist(id));
		}
	}

	int remaining = 20 - result.size();
	if (remaining <= 0) {
		return result;
	}

	// get tracks
	query.prepare(
		"SELECT t.id "
		"FROM artist_track a_t "
		"INNER JOIN track t ON a_t.track_id = t.id "
		"INNER JOIN artist a ON a_t.artist_id = a.id "
		"WHERE t.title LIKE :keyword OR a.name LIKE :keyword LIMIT :limit");
	query.bindValue(":keyword", QString("%%1%").arg(keyword));
	query.bindValue(":limit", remaining);

	if (query.exec()) {
		while (query.next()) {
			TrackId id = query.value(0).toULongLong();
			result.append(getTrack(id));
		}
	}

	// get playlists
	remaining = 20 - result.size();
	if (remaining <= 0) {
		return result;
	}

	query.prepare("SELECT id FROM playlist "
				  "WHERE name LIKE :keyword "
				  "LIMIT :limit");
	query.bindValue(":keyword", QString("%%1%").arg(keyword));
	query.bindValue(":limit", remaining);

	if (query.exec()) {
		while (query.next()) {
			PlaylistId id = query.value(0).toULongLong();
			result.append(getPlaylist(id));
		}
	}

	return result;
}

QList<Artist*> ResourceManager::getAllArtists() {
	QSqlQuery query(mDatabase);
	query.prepare("SELECT id FROM artist");

	QList<Artist*> result;

	if (query.exec()) {
		while (query.next()) {
			ArtistId id = query.value(0).toULongLong();
			result.append(getArtist(id));
		}
	}

	return result;
}

QList<Playlist*> ResourceManager::getAllPlaylists() {
	QSqlQuery query(mDatabase);
	query.prepare("SELECT id FROM playlist");

	QList<Playlist*> result;

	if (query.exec()) {
		while (query.next()) {
			PlaylistId id = query.value(0).toULongLong();
			result.append(getPlaylist(id));
		}
	}

	return result;
}

QList<Playlist*> ResourceManager::getPlaylistsByArtist(ArtistId artistId) {
	QSqlQuery query(mDatabase);
	query.prepare("SELECT playlist_id FROM artist_playlist "
				  "WHERE artist_id = :id "
				  "ORDER BY playlist_priority ASC");
	query.bindValue(":id", static_cast<qlonglong>(artistId));

	QList<Playlist*> result;

	if (query.exec()) {
		while (query.next()) {
			PlaylistId id = query.value(0).toULongLong();
			result.append(getPlaylist(id));
		}
	}

	return result;
}

Artist* ResourceManager::getArtistByPlaylist(PlaylistId playlistId) {
	QSqlQuery query(mDatabase);
	query.prepare("SELECT artist_id FROM artist_playlist "
				  "WHERE playlist_id = :id");
	query.bindValue(":id", static_cast<qlonglong>(playlistId));

	if (query.exec() && query.next()) {
		ArtistId id = query.value(0).toULongLong();
		return getArtist(id);
	} else {
		return nullptr;
	}
}
