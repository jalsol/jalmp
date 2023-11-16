#include "TrackBuilder.hpp"

#include <QDebug>

TrackBuilder& TrackBuilder::setId(TrackId id) {
	mTrack.setId(id);
	return *this;
}

TrackBuilder& TrackBuilder::setTitle(const QString& title) {
	mTrack.setTitle(title);
	return *this;
}

TrackBuilder& TrackBuilder::setDuration(const QTime& duration) {
	mTrack.setDuration(duration);
	return *this;
}

TrackBuilder& TrackBuilder::setCover(const QString& cover) {
	mTrack.setCover(cover);
	return *this;
}

Track TrackBuilder::build() const { return mTrack; }
