#include "EntityButton.hpp"

#include "Navigator.hpp"

EntityButton::EntityButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this, &EntityButton::onClicked);
}

EntityButton::EntityButton(Entity *entity, PlaylistId playlistId,
						   QWidget *parent)
	: EntityButton{parent} {
	mPlaylistId = playlistId;

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

void EntityButton::onClicked() { Navigator::instance()->navigateTo(mPath); }
