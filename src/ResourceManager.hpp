#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "Artist.hpp"
#include "Entity.hpp"
#include "Playlist.hpp"
#include "Track.hpp"
#include "Types.hpp"

#include <QList>
#include <QPair>
#include <QtSql>
#include <list>

class ResourceManager {
public:
	static ResourceManager& instance();
	Artist* getArtist(ArtistId id);
	Track* getTrack(TrackId id);
	Playlist* getPlaylist(PlaylistId id);

	// [[nodiscard]] bool saveArtist(Artist& artist);
	// [[nodiscard]] bool 1saveTrack(Track& track);
	// [[nodiscard]] bool savePlaylist(Playlist& playlist);

	QList<Track*> getTracksByPlaylist(PlaylistId playlistId);
	QList<Track*> getTracksByArtist(ArtistId artistId);
	QList<Artist*> getArtistsByTrack(TrackId trackId);
	QList<Entity*> getEntitiesByKeyword(const QString& keyword);
	QList<Artist*> getAllArtists();

private:
	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	QSqlDatabase mDatabase;

	// entities
	std::list<Artist> mArtists;
	std::list<Track> mTracks;
	std::list<Playlist> mPlaylists;

	// relations
	// QList<QPair<ArtistId, TrackId>> mRelArtistTrack;
	// QList<QPair<PlaylistId, TrackId>> mRelPlaylistTrack;
	// QList<QPair<ArtistId, PlaylistId>> mRelArtistPlaylist;
};

#endif // RESOURCEMANAGER_HPP
