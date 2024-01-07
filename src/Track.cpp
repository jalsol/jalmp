#include "Track.hpp"

// EntityId Track::id() const { return mId; }

// QString Track::name() const { return mName; }

QTime Track::duration() const { return mDuration; }

EntityType Track::type() const { return EntityType::Track; }

// QString Track::cover() const { return mCover; }

// void Track::setId(EntityId id) { mId = id; }

// void Track::setName(const QString& name) { mName = name; }

void Track::setDuration(const QTime& duration) { mDuration = duration; }

// void Track::setCover(const QString& cover) { mCover = cover; }
