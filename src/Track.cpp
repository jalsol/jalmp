#include "Track.hpp"

QTime Track::duration() const { return mDuration; }

QString Track::url() const { return mUrl; }

EntityType Track::type() const { return EntityType::Track; }

void Track::setDuration(const QTime& duration) { mDuration = duration; }

void Track::setUrl(const QString& url) { mUrl = url; }
