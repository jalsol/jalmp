#ifndef ENTITYLISTBUTTON_HPP
#define ENTITYLISTBUTTON_HPP

#include "Entity.hpp"

#include <QPushButton>

class EntityListButton : public QPushButton {
public:
	EntityListButton(QWidget *parent = nullptr);
	EntityListButton(Entity *entity, QWidget *parent = nullptr);
};

#endif // ENTITYLISTBUTTON_HPP
