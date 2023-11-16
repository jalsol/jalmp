#ifndef ARTIST_H
#define ARTIST_H

#include "Types.hpp"

#include <QList>
#include <QString>

// forward-declared
class Track;

class Artist {
public:
	ArtistId id() const;
	QString name() const;
	QList<Track> tracks() const;
	QString cover() const;

private:
	friend class ArtistBuilder;
	friend class ResourceManager;

	void setId(ArtistId id);
	void setName(const QString& name);
	void setCover(const QString& cover);

	ArtistId mId = ArtistId::Invalid;
	QString mName;
	QString mCover;
};

#endif // ARTIST_H
