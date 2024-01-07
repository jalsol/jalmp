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
	TrackBuilder& setName(const QString& Name);
	TrackBuilder& setDuration(const QTime& duration);
	TrackBuilder& setCover(const QString& cover);
	TrackBuilder& setUrl(const QString& url);
	Track build() const;

private:
	Track mTrack;
};

#endif // TRACKBUILDER_H
