#include "ArtistBuilder.hpp"

ArtistBuilder& ArtistBuilder::setId(ArtistId id) {
	mArtist.setId(id);
	return *this;
}

ArtistBuilder& ArtistBuilder::setName(const QString& name) {
	mArtist.setName(name);
	return *this;
}

ArtistBuilder& ArtistBuilder::setCover(const QString& cover) {
	mArtist.setCover(cover);
	return *this;
}

Artist ArtistBuilder::build() const { return mArtist; }
