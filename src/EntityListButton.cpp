#include "EntityListButton.hpp"

#include "Navigator.hpp"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

EntityListButton::EntityListButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this, &EntityListButton::onClicked);
}

EntityListButton::EntityListButton(Entity *entity, PlaylistId playlistId,
								   QWidget *parent)
	: EntityListButton{parent} {
	mPlaylistId = playlistId;
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

	// set data
	switch (entity->type()) {
	case EntityType::Artist:
		mPath = QString("artist/%1").arg(entity->id());
		break;
	case EntityType::Playlist:
		mPath = QString("playlist/%1").arg(entity->id());
		break;
	case EntityType::Track:
		mPath = QString("playlist/%1/track/%2")
					.arg(QString::number(mPlaylistId),
						 QString::number(entity->id()));
		break;
	default:
		__builtin_unreachable();
	}
}

void EntityListButton::onClicked() { Navigator::instance()->navigateTo(mPath); }
