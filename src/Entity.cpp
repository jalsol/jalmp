#include "Entity.hpp"

EntityId Entity::id() const { return mId; }

QString Entity::name() const { return mName; }

QString Entity::cover() const { return mCover; }

void Entity::setId(EntityId id) { mId = id; }

void Entity::setName(const QString& name) { mName = name; }

void Entity::setCover(const QString& cover) { mCover = cover; }
