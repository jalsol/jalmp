#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "Artist.hpp"
#include "Entity.hpp"
#include "Playlist.hpp"
#include "Track.hpp"
#include "Types.hpp"

#include <QList>
#include <QtSql>
#include <list>

class ResourceManager : public QObject {
	Q_OBJECT
public:
	static ResourceManager& instance();
	Artist* getArtist(ArtistId id);
	Track* getTrack(TrackId id);
	Playlist* getPlaylist(PlaylistId id);

	QList<Track*> getTracksByPlaylist(PlaylistId playlistId);
	QList<Track*> getTracksByArtist(ArtistId artistId);
	QList<Artist*> getArtistsByTrack(TrackId trackId);
	QList<Entity*> getEntitiesByKeyword(const QString& keyword);
	QList<Artist*> getAllArtists();
	QList<Playlist*> getAllPlaylists();
	QList<Playlist*> getPlaylistsByArtist(ArtistId artistId);
	Artist* getArtistByPlaylist(PlaylistId playlistId);
	QList<Track*> getAllFavoriteTracks();

public slots:
	void setTrackFavorite(TrackId trackId, bool favourite);

signals:
	void trackFavoriteChanged(TrackId trackId, bool favorite);

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
};

#endif // RESOURCEMANAGER_HPP
