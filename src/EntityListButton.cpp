#include "EntityListButton.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

EntityListButton::EntityListButton(QWidget *parent) : QPushButton(parent) {}

EntityListButton::EntityListButton(Entity *entity, QWidget *parent)
	: QPushButton(parent) {
	auto layout = new QHBoxLayout(this);

	// load cover image
	QPixmap pixmap;
	pixmap.load("../../" + entity->cover());
	auto *cover = new QLabel();
	cover->setPixmap(
		pixmap.scaled(35, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	cover->setFixedWidth(50);
	layout->addWidget(cover);

	// load text
	const auto text = QString("%1: %2").arg(
		Entity::typeToString(entity->type()), entity->name());
	auto *label = new QLabel(text);
	label->setAlignment(Qt::AlignCenter);
	layout->addWidget(label);

	setLayout(layout);
	setFixedHeight(50);
}
