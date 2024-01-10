#include "Entity.hpp"

EntityId Entity::id() const { return mId; }

QString Entity::name() const { return mName; }

QString Entity::cover() const { return mCover; }

EntityType Entity::type() const { return EntityType::Default; }

bool Entity::isFavorite() const { return false; }

QString Entity::typeToString(EntityType type) {
	switch (type) {
	case EntityType::Artist:
		return "Artist";
	case EntityType::Playlist:
		return "Playlist";
	case EntityType::Track:
		return "Track";
	default:
		return "Default";
	}
}

void Entity::setId(EntityId id) { mId = id; }

void Entity::setName(const QString& name) { mName = name; }

void Entity::setCover(const QString& cover) { mCover = cover; }
