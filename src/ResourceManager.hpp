#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "Artist.hpp"
#include "Playlist.hpp"
#include "Track.hpp"
#include "Types.hpp"

#include <QList>
#include <QPair>
#include <QtSql>

class ResourceManager {
public:
	static ResourceManager& instance();
	Artist* getArtist(ArtistId id);
	Track* getTrack(TrackId id);
	Playlist* getPlaylist(PlaylistId id);

	[[nodiscard]] bool saveArtist(Artist& artist);
	[[nodiscard]] bool saveTrack(Track& track);
	[[nodiscard]] bool savePlaylist(Playlist& playlist);

	QList<Track*> getTracksByArtist(ArtistId artistId);
	QList<Artist*> getArtistsByTrack(TrackId trackId);

private:
	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	QSqlDatabase mDatabase;

	// entities
	QList<Artist> mArtists;
	QList<Track> mTracks;
	QList<Playlist> mPlaylists;

	// relations
	QList<QPair<ArtistId, TrackId>> mRelArtistTrack;
	QList<QPair<PlaylistId, TrackId>> mRelPlaylistTrack;
	QList<QPair<ArtistId, PlaylistId>> mRelArtistPlaylist;
};

#endif // RESOURCEMANAGER_HPP
