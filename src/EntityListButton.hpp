#ifndef ENTITYLISTBUTTON_HPP
#define ENTITYLISTBUTTON_HPP

#include "EntityButton.hpp"

class EntityListButton : public EntityButton {
public:
	EntityListButton(QWidget *parent = nullptr);
	EntityListButton(Entity *entity,
					 PlaylistId playlistId = PlaylistId::Invalid,
					 QWidget *parent = nullptr);
};

#endif // ENTITYLISTBUTTON_HPP
