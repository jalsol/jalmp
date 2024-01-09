#include "Track.hpp"

QTime Track::duration() const { return mDuration; }

QString Track::url() const { return mUrl; }

EntityType Track::type() const { return EntityType::Track; }

bool Track::isFavorite() const { return mIsFavorite; }

void Track::setDuration(const QTime& duration) { mDuration = duration; }

void Track::setUrl(const QString& url) { mUrl = url; }

void Track::setFavorite(bool isFavorite) { mIsFavorite = isFavorite; }
