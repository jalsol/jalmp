#include "EntityListButton.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

EntityListButton::EntityListButton(QWidget *parent) : EntityButton(parent) {}

EntityListButton::EntityListButton(Entity *entity, PlaylistId playlistId,
								   QWidget *parent)
	: EntityButton(entity, playlistId, parent) {
	auto layout = new QHBoxLayout(this);

	// load cover image
	QPixmap pixmap;
	pixmap.load("../.." + entity->cover());
	auto *cover = new QLabel();
	cover->setPixmap(
		pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	cover->setFixedWidth(35);
	layout->addWidget(cover);

	// load text
	const auto text = QString("%1").arg(entity->name());
	auto *label = new QLabel(text);
	label->setAlignment(Qt::AlignCenter);
	layout->addWidget(label);

	layout->setSpacing(0);
	layout->setContentsMargins(5, 5, 5, 5);

	setLayout(layout);
	setFixedHeight(35);
}
