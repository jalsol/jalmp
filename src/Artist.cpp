#include "Artist.hpp"

EntityType Artist::type() const { return EntityType::Artist; }

PlaylistId Artist::discography() const { return mDiscographyId; }

void Artist::setDiscography(PlaylistId discographyId) {
	mDiscographyId = discographyId;
}
