#ifndef ARTISTBUILDER_HPP
#define ARTISTBUILDER_HPP

#include "Artist.hpp"
#include "Types.hpp"

class ArtistBuilder {
public:
	friend class ResourceManager;

	ArtistBuilder& setId(ArtistId id);
	ArtistBuilder& setName(const QString& name);
	ArtistBuilder& setCover(const QString& cover);
	ArtistBuilder& setDiscography(PlaylistId discographyId);

	Artist build() const;

private:
	Artist mArtist;
};

#endif // ARTISTBUILDER_HPP
