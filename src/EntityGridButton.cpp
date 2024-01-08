#include "EntityGridButton.hpp"

#include <QLabel>
#include <QVBoxLayout>

EntityGridButton::EntityGridButton(QWidget *parent) : EntityButton(parent) {}

EntityGridButton::EntityGridButton(Entity *entity, PlaylistId playlistId,
								   QWidget *parent)
	: EntityButton(entity, playlistId, parent) {
	auto layout = new QVBoxLayout(this);

	// load cover image
	QPixmap pixmap;
	pixmap.load("../../" + entity->cover());
	auto *cover = new QLabel();
	cover->setPixmap(
		pixmap.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	cover->setFixedWidth(200);
	layout->addWidget(cover);

	// load text
	const auto text = QString("%1").arg(entity->name());
	auto *label = new QLabel(text);
	label->setAlignment(Qt::AlignCenter);
	layout->addWidget(label);

	setLayout(layout);
	setFixedHeight(230);
	setFixedWidth(200);
}
