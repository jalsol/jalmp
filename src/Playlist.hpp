#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "Entity.hpp"
// #include "Types.hpp"

#include <QString>

class Playlist : public Entity {
public:
	// EntityId id() const override;
	// QString name() const override;
	// QString cover() const override;

private:
	friend class PlaylistBuilder;
	friend class ResourceManager;

	// void setId(EntityId id) override;
	// void setName(const QString& name) override;
	// void setCover(const QString& cover) override;

	// using Entity::mCover;
	// using Entity::mId;
	// using Entity::mName;
};

#endif // PLAYLIST_HPP
