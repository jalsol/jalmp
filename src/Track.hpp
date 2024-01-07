#ifndef TRACK_H
#define TRACK_H

#include "Entity.hpp"
// #include "Types.hpp"

#include <QString>
#include <QTime>

class Track : public Entity {
public:
	// EntityId id() const override;
	// QString name() const override;
	// QString cover() const override;

	QTime duration() const;

private:
	friend class TrackBuilder;
	friend class ResourceManager;

	// void setId(EntityId id) override;
	// void setName(const QString& name) override;
	// void setCover(const QString& cover) override;
	void setDuration(const QTime& duration);

	// using Entity::mCover;
	// using Entity::mId;
	// using Entity::mName;
	QTime mDuration{0, 0, 0, 0};
};

#endif // TRACK_H
