#ifndef ARTIST_H
#define ARTIST_H

#include "Entity.hpp"

#include <QString>

class Artist : public Entity {
public:
	EntityType type() const override;

private:
	friend class ArtistBuilder;
	friend class ResourceManager;
};

#endif // ARTIST_H
