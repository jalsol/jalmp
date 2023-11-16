#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "Types.hpp"

#include <QList>
#include <QString>

// forward-declared
class Track;

class Playlist {
public:
	PlaylistId id() const;
	QString name() const;
	QList<Track> tracks() const;

private:
	friend class PlaylistBuilder;
	friend class ResourceManager;

	void setId(PlaylistId id);
	void setName(const QString& name);
	void setCover(const QString& cover);

	PlaylistId mId = PlaylistId::Invalid;
	QString mName;
	QString mCover;
};

#endif // PLAYLIST_HPP
