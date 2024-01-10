#include "TrackListPage.hpp"

#include "AddQueueButton.hpp"
#include "DurationLabel.hpp"
#include "EntityListButton.hpp"
#include "FavoriteButton.hpp"
#include "IndexLabel.hpp"
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
		int col = 0;
		{
			auto *idLabel = new IndexLabel(row + 1);
			layout->addWidget(idLabel, row, col++, Qt::AlignTop);
		}

		{
			auto *durationLabel = new DurationLabel(track->duration());
			layout->addWidget(durationLabel, row, col++, Qt::AlignTop);
		}

		{
			EntityListButton *trackButton;
			if (mType == EntityType::Playlist) {
				trackButton = new EntityListButton(track, (qint64)mId);
			} else {
				trackButton = new EntityListButton(track);
			}
			layout->addWidget(trackButton, row, col++, Qt::AlignTop);
		}

		{
			auto *favoriteButton =
				new FavoriteButton((qint64)track->id(), track->isFavorite());
			layout->addWidget(favoriteButton, row, col++, Qt::AlignTop);
		}

		{
			auto *addQueueButton = new AddQueueButton((qint64)track->id());
			layout->addWidget(addQueueButton, row, col++, Qt::AlignTop);
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
