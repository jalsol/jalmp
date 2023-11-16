#include "Playlist.hpp"

#include "Track.hpp"

PlaylistId Playlist::id() const { return mId; }

QString Playlist::name() const { return mName; }

QList<Track> Playlist::tracks() const { Q_ASSERT(false && "Not implemented"); }

void Playlist::setId(PlaylistId id) { mId = id; }

void Playlist::setName(const QString& name) { mName = name; }

void Playlist::setCover(const QString& cover) { mCover = cover; }
