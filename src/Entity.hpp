#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Types.hpp"

#include <QString>

class Entity {
public:
	virtual EntityId id() const;
	virtual QString name() const;
	virtual QString cover() const;
	virtual EntityType type() const;

	static QString typeToString(EntityType type);
	virtual bool isFavorite() const;

protected:
	virtual void setId(EntityId id);
	virtual void setName(const QString& name);
	virtual void setCover(const QString& cover);

	EntityId mId;
	QString mName;
	QString mCover;
};

#endif // ENTITY_HPP
