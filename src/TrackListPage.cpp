#include "TrackListPage.hpp"

#include "EntityListButton.hpp"
#include "MediaQueue.hpp"
#include "ResourceManager.hpp"

#include <QGridLayout>

TrackListPage::TrackListPage(QWidget *parent) : Page(parent) {}

void TrackListPage::fillList() {
	ResourceManager &rm = ResourceManager::instance();
	Entity *entity = (mType == EntityType::Playlist)
						 ? (Entity *)rm.getPlaylist((qint64)mId)
						 : (Entity *)rm.getArtist((qint64)mId);

	// load cover and set name
	mPixmap.load("../../" + entity->cover());
	cover()->setPixmap(mPixmap.scaled(200, 200, Qt::KeepAspectRatio,
									  Qt::SmoothTransformation));
	name()->setText(entity->name());

	// display tracks in the QScrollArea
	QList<Track *> tracks = (mType == EntityType::Playlist)
								? rm.getTracksByPlaylist((qint64)mId)
								: rm.getTracksByArtist((qint64)mId);
	MediaQueue::instance().setPlaylist(tracks);
	QGridLayout *layout = new QGridLayout{scrollList()};
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 4; ++col) {
		layout->setColumnStretch(col, 1);
	}

	int row = 0;
	for (auto *track : tracks) {
		auto *idLabel = new QLabel();
		idLabel->setText(QString::number(row + 1));
		idLabel->setFixedSize(50, 50);
		idLabel->setAlignment(Qt::AlignCenter);
		layout->addWidget(idLabel, row, 0, Qt::AlignTop);

		EntityListButton *trackButton;
		if (mType == EntityType::Playlist) {
			trackButton = new EntityListButton(track, (qint64)mId);
		} else {
			trackButton = new EntityListButton(track);
		}
		layout->addWidget(trackButton, row, 1, Qt::AlignTop);

		auto *likeButton = new QPushButton();
		// likeButton->setIcon(QIcon(":/icons/like.png"));
		likeButton->setText("Like");
		likeButton->setFixedSize(50, 50);
		layout->addWidget(likeButton, row, 2, Qt::AlignTop);

		auto *durationLabel = new QLabel();
		durationLabel->setText(track->duration().toString("mm:ss"));
		durationLabel->setFixedSize(50, 50);
		durationLabel->setAlignment(Qt::AlignCenter);
		layout->addWidget(durationLabel, row, 3, Qt::AlignTop);

		++row;
	}

	if (row > 0) {
		layout->setRowStretch(row - 1, 1);
	}

	// set the scroll area's widget
	scrollList()->setLayout(layout);
}

void TrackListPage::loadTrackFrom(EntityId id, EntityType type) {
	if (id == mId && type == mType) {
		return;
	}

	mId = id;
	mType = type;
	clearList();
	fillList();
}

QPair<EntityId, EntityType> TrackListPage::id() const { return {mId, mType}; }

const char *TrackListPage::scrollListName() const { return "tracklist"; }

QLabel *TrackListPage::cover() {
	if (mCover == nullptr) {
		mCover = findChild<QLabel *>("tracklistCoverLabel");
	}

	return mCover;
}

QLabel *TrackListPage::name() {
	if (mName == nullptr) {
		mName = findChild<QLabel *>("tracklistNameLabel");
	}

	return mName;
}

QPushButton *TrackListPage::viewOrigin() {
	if (mViewOrigin == nullptr) {
		mViewOrigin = findChild<QPushButton *>("viewTracklistOrigin");
	}

	return mViewOrigin;
}
