#ifndef ENTITYGRIDBUTTON_HPP
#define ENTITYGRIDBUTTON_HPP

#include "EntityButton.hpp"

class EntityGridButton : public EntityButton {
public:
	EntityGridButton(QWidget *parent = nullptr);
	EntityGridButton(Entity *entity,
					 PlaylistId playlistId = PlaylistId::Invalid,
					 QWidget *parent = nullptr);
};

#endif // ENTITYGRIDBUTTON_HPP
