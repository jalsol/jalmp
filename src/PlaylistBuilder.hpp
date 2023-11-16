#ifndef PLAYLISTBUILDER_HPP
#define PLAYLISTBUILDER_HPP

#include "Playlist.hpp"
#include "Types.hpp"

class PlaylistBuilder {
public:
	PlaylistBuilder() = default;

	PlaylistBuilder& setId(PlaylistId id);
	PlaylistBuilder& setName(const QString& name);
	PlaylistBuilder& setCover(const QString& cover);

	Playlist build() const;

private:
	Playlist mPlaylist;
};

#endif // PLAYLISTBUILDER_HPP
