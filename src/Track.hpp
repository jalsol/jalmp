#ifndef TRACK_H
#define TRACK_H

#include "Entity.hpp"

#include <QString>
#include <QTime>

class Track : public Entity {
public:
	QTime duration() const;
	EntityType type() const override;
	QString url() const;

private:
	friend class TrackBuilder;
	friend class ResourceManager;

	void setDuration(const QTime& duration);
	void setUrl(const QString& url);

	QTime mDuration{0, 0, 0, 0};
	QString mUrl;
};

#endif // TRACK_H
