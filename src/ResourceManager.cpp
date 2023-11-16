#include "ResourceManager.hpp"

#include "ArtistBuilder.hpp"
#include "PlaylistBuilder.hpp"
#include "TrackBuilder.hpp"

ResourceManager::ResourceManager() {
	mDatabase = QSqlDatabase::addDatabase("QMARIADB");
	mDatabase.setHostName("localhost");
	mDatabase.setPort(3306);
	mDatabase.setDatabaseName("jalmp");
	mDatabase.setUserName("root");
	mDatabase.setPassword(""password"");

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
	query.prepare("SELECT * FROM artist WHERE id = :id");
	query.bindValue(":id", static_cast<qlonglong>(id));

	if (!query.exec()) {
		return nullptr;
	}

	if (query.next()) {
		QString name = query.value(1).toString();
		QString cover = query.value(2).toString();
		Artist artist =
			ArtistBuilder().setId(id).setName(name).setCover(cover).build();
		mArtists.append(artist);

		return &mArtists.last();
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
	query.prepare("SELECT * FROM track WHERE id = :id");
	query.bindValue(":id", static_cast<qlonglong>(id));

	if (!query.exec()) {
		qDebug() << "exec failed\n";
		return nullptr;
	}

	if (query.next()) {
		QString title = query.value(1).toString();
		QTime duration = query.value(2).toTime();
		QString cover = query.value(3).toString();

		Track track = TrackBuilder()
						  .setId(id)
						  .setTitle(title)
						  .setDuration(duration)
						  .setCover(cover)
						  .build();

		mTracks.append(track);

		return &mTracks.last();
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
	query.prepare("SELECT * FROM playlist WHERE id = :id");
	query.bindValue(":id", static_cast<qlonglong>(id));

	if (!query.exec()) {
		return nullptr;
	}

	if (!query.next()) {
		QString name = query.value(1).toString();
		QString cover = query.value(2).toString();

		Playlist playlist =
			PlaylistBuilder().setId(id).setName(name).setCover(cover).build();
		mPlaylists.append(playlist);

		return &mPlaylists.last();
	} else {
		return nullptr;
	}
}

bool ResourceManager::saveArtist(Artist& artist) {
	QSqlQuery query(mDatabase);
	query.prepare("INSERT INTO artist (name) VALUES (:name)");
	query.bindValue(":name", artist.name());

	if (query.exec()) {
		ArtistId id = static_cast<ArtistId>(query.lastInsertId().toULongLong());
		artist.setId(id);
		mArtists.append(artist);
		return true;
	} else {
		return false;
	}
}

bool ResourceManager::saveTrack(Track& track) {
	QSqlQuery query(mDatabase);
	query.prepare(
		"INSERT INTO track (title, duration) VALUES (:title, :duration)");
	query.bindValue(":title", track.title());
	query.bindValue(":duration", track.duration());

	if (query.exec()) {
		TrackId id = static_cast<TrackId>(query.lastInsertId().toULongLong());
		track.setId(id);
		mTracks.append(track);
		return true;
	} else {
		return false;
	}
}

bool ResourceManager::savePlaylist(Playlist& playlist) {
	QSqlQuery query(mDatabase);
	query.prepare("INSERT INTO playlist (name) VALUES (:name)");
	query.bindValue(":name", playlist.name());

	if (query.exec()) {
		PlaylistId id =
			static_cast<PlaylistId>(query.lastInsertId().toULongLong());
		playlist.setId(id);
		mPlaylists.append(playlist);
		return true;
	} else {
		return false;
	}
}

QList<Track*> ResourceManager::getTracksByArtist(ArtistId artistId) {
	QSqlQuery query(mDatabase);
	query.prepare(
		"SELECT track_id FROM artist_track WHERE artist_id = :artist_id");
	query.bindValue(":artist_id", static_cast<qlonglong>(artistId));

	QList<Track*> result;

	if (query.exec()) {
		QList<TrackId> trackIds;

		while (query.next()) {
			TrackId id = static_cast<TrackId>(query.value(0).toULongLong());
			trackIds.append(id);

			// temporarily ignore return the pointer
			// as we are only fetching the tracks

			// prefetch is required, since pointer values will be invalid
			// if mTracks is reallocated
			// TODO: could be solved using a linked list
			getTrack(id);
		}

		for (auto& track : mTracks) {
			if (trackIds.contains(track.id())) {
				result.append(&track);
			}
		}
	}

	return result;
}

QList<Artist*> ResourceManager::getArtistsByTrack(TrackId trackId) {
	QSqlQuery query(mDatabase);
	query.prepare(
		"SELECT artist_id FROM artist_track WHERE track_id = :track_id");
	query.bindValue(":track_id", static_cast<qlonglong>(trackId));

	QList<Artist*> result;

	if (query.exec()) {
		while (query.next()) {
			ArtistId id = static_cast<ArtistId>(query.value(0).toULongLong());
			Artist* artist = getArtist(id);
			result.append(artist);
		}
	}

	return result;
}
