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
	auto *label = new QLabel(entity->name());
	label->setAlignment(Qt::AlignCenter);
	layout->addWidget(label);

	setLayout(layout);
	setFixedHeight(50);
}
