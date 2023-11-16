#ifndef TRACKBUILDER_H
#define TRACKBUILDER_H

#include "Artist.hpp"
#include "Track.hpp"
#include "Types.hpp"

#include <QString>
#include <QTime>

class TrackBuilder {
public:
	friend class ResourceManager;

	TrackBuilder& setId(TrackId id);
	TrackBuilder& setTitle(const QString& title);
	TrackBuilder& setDuration(const QTime& duration);
	TrackBuilder& setCover(const QString& cover);
	Track build() const;

private:
	Track mTrack;
};

#endif // TRACKBUILDER_H
