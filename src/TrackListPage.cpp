#include "TrackListPage.hpp"

#include "EntityListButton.hpp"
#include "FavoriteButton.hpp"
#include "MediaQueue.hpp"
#include "ResourceManager.hpp"

#include <QGridLayout>

TrackListCapture::TrackListCapture(QWidget *parent)
	: ScrollListCapture(parent) {}

TrackListCapture::TrackListCapture(const QString &name, QWidget *parent)
	: ScrollListCapture(name, parent) {}

void TrackListCapture::loadTrackFrom(EntityId id, EntityType type) {
	if (mId == id && mType == type) {
		return;
	}

	mId = id;
	mType = type;
	reload();
}

void TrackListCapture::fill() {
	ResourceManager &rm = ResourceManager::instance();

	QList<Track *> tracks = (mType == EntityType::Playlist)
								? rm.getTracksByPlaylist((qint64)mId)
								: rm.getTracksByArtist((qint64)mId);
	MediaQueue::instance().setPlaylist(tracks);

	QGridLayout *layout = new QGridLayout{get()};
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 4; ++col) {
		layout->setColumnStretch(col, 1);
	}

	int row = 0;
	for (auto *track : tracks) {
		{
			auto *idLabel = new QLabel();
			idLabel->setText(QString::number(row + 1));
			idLabel->setFixedSize(20, 50);
			idLabel->setAlignment(Qt::AlignCenter);
			layout->addWidget(idLabel, row, 0, Qt::AlignTop);
		}

		{
			auto *durationLabel = new QLabel();
			durationLabel->setText(track->duration().toString("mm:ss"));
			durationLabel->setFixedSize(50, 50);
			durationLabel->setAlignment(Qt::AlignCenter);
			layout->addWidget(durationLabel, row, 1, Qt::AlignTop);
		}

		{
			EntityListButton *trackButton;
			if (mType == EntityType::Playlist) {
				trackButton = new EntityListButton(track, (qint64)mId);
			} else {
				trackButton = new EntityListButton(track);
			}
			layout->addWidget(trackButton, row, 2, Qt::AlignTop);
		}

		{
			auto *favoriteButton =
				new FavoriteButton((qint64)track->id(), track->isFavorite());
			layout->addWidget(favoriteButton, row, 3, Qt::AlignTop);
		}

		++row;
	}

	if (row > 0) {
		layout->setRowStretch(row - 1, 1);
	}

	// set the scroll area's widget
	get()->setLayout(layout);
}

QPair<EntityId, EntityType> TrackListCapture::id() const {
	return {mId, mType};
}

TrackListPage::TrackListPage(QWidget *parent) : Page(parent) {}

void TrackListPage::fill(EntityId id, EntityType type) {
	ResourceManager &rm = ResourceManager::instance();

	Entity *entity = (type == EntityType::Playlist)
						 ? (Entity *)rm.getPlaylist((qint64)id)
						 : (Entity *)rm.getArtist((qint64)id);

	// load cover and set name
	mPixmap.load("../../" + entity->cover());
	mCover.get()->setPixmap(mPixmap.scaled(200, 200, Qt::KeepAspectRatio,
										   Qt::SmoothTransformation));
	mName.get()->setText(entity->name());

	mList.loadTrackFrom(id, type);
}

QPair<EntityId, EntityType> TrackListPage::id() const { return mList.id(); }

void TrackListPage::reload() { mList.reload(); }
