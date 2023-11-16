#include "PlaylistBuilder.hpp"

PlaylistBuilder& PlaylistBuilder::setId(PlaylistId id) {
	mPlaylist.setId(id);
	return *this;
}

PlaylistBuilder& PlaylistBuilder::setName(const QString& name) {
	mPlaylist.setName(name);
	return *this;
}

PlaylistBuilder& PlaylistBuilder::setCover(const QString& cover) {
	mPlaylist.setCover(cover);
	return *this;
}

Playlist PlaylistBuilder::build() const { return mPlaylist; }
