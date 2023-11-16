#include "Track.hpp"

TrackId Track::id() const { return mId; }

QString Track::title() const { return mTitle; }

QTime Track::duration() const { return mDuration; }

QString Track::cover() const { return mCover; }

void Track::setId(TrackId id) { mId = id; }

void Track::setTitle(const QString& title) { mTitle = title; }

void Track::setDuration(const QTime& duration) { mDuration = duration; }

void Track::setCover(const QString& cover) { mCover = cover; }
