#ifndef TRACK_H
#define TRACK_H

#include "Artist.hpp"
#include "Types.hpp"

#include <QList>
#include <QString>
#include <QTime>

class Track
{
public:
	TrackId id() const;
	QString title() const;
	QTime duration() const;
	QString cover() const;

private:
	friend class TrackBuilder;
	friend class ResourceManager;

	void setId(TrackId id);
	void setTitle(const QString& title);
	void setDuration(const QTime& duration);
	void setCover(const QString& cover);

	TrackId mId = TrackId::Invalid;
	QString mTitle;
	QTime mDuration{0, 0, 0, 0};
	QString mCover;
};

#endif // TRACK_H
