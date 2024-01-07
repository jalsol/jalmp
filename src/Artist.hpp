#ifndef ARTIST_H
#define ARTIST_H

#include "Entity.hpp"
#include "Types.hpp"

#include <QString>

class Artist : public Entity {
public:
	EntityType type() const override;
	PlaylistId discography() const;

private:
	friend class ArtistBuilder;
	friend class ResourceManager;

	void setDiscography(PlaylistId discographyId);

	PlaylistId mDiscographyId;
};

#endif // ARTIST_H
