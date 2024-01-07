#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Types.hpp"

#include <QString>

enum class EntityType : int64_t { Default, Artist, Playlist, Track };

class Entity {
public:
	virtual EntityId id() const;
	virtual QString name() const;
	virtual QString cover() const;
	virtual EntityType type() const;

	static QString typeToString(EntityType type);

protected:
	virtual void setId(EntityId id);
	virtual void setName(const QString& name);
	virtual void setCover(const QString& cover);

	EntityId mId;
	QString mName;
	QString mCover;
};

#endif // ENTITY_HPP
