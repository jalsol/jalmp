#include "Artist.hpp"

#include "Track.hpp"

ArtistId Artist::id() const { return mId; }

QString Artist::name() const { return mName; }

QList<Track> Artist::tracks() const { Q_ASSERT(false && "Not implemented"); }

QString Artist::cover() const { return mCover; }

void Artist::setId(ArtistId id) { mId = id; }

void Artist::setName(const QString& name) { mName = name; }

void Artist::setCover(const QString& cover) { mCover = cover; }
