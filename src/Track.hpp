#ifndef TRACK_H
#define TRACK_H

#include "Entity.hpp"

#include <QString>
#include <QTime>

class Track : public Entity {
public:
	QTime duration() const;
	EntityType type() const override;

private:
	friend class TrackBuilder;
	friend class ResourceManager;

	void setDuration(const QTime& duration);

	QTime mDuration{0, 0, 0, 0};
};

#endif // TRACK_H
