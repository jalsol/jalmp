#include "TrackBuilder.hpp"

#include <QDebug>

TrackBuilder& TrackBuilder::setId(TrackId id) {
	mTrack.setId(id);
	return *this;
}

TrackBuilder& TrackBuilder::setName(const QString& name) {
	mTrack.setName(name);
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

TrackBuilder& TrackBuilder::setUrl(const QString& url) {
	mTrack.setUrl(url);
	return *this;
}

TrackBuilder& TrackBuilder::setFavorite(bool isFavorite) {
	mTrack.setFavorite(isFavorite);
	return *this;
}

Track TrackBuilder::build() const { return mTrack; }
