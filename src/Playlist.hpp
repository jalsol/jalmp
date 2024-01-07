#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "Entity.hpp"

#include <QString>

class Playlist : public Entity {
public:
	EntityType type() const override;

private:
	friend class PlaylistBuilder;
	friend class ResourceManager;
};

#endif // PLAYLIST_HPP
