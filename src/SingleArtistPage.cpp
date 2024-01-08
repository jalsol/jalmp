#include "SingleArtistPage.hpp"

#include "EntityListButton.hpp"
#include "MediaQueue.hpp"
#include "ResourceManager.hpp"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QList>

SingleArtistPage::SingleArtistPage(QWidget *parent) : Page(parent) {}

void SingleArtistPage::fillList() {
	ResourceManager &rm = ResourceManager::instance();
	Artist *artist = rm.getArtist(mArtistId);
	Q_ASSERT(artist != nullptr);

	// load cover and set name
	mPixmap.load("../../" + artist->cover());
	cover()->setPixmap(mPixmap.scaled(200, 200, Qt::KeepAspectRatio,
									  Qt::SmoothTransformation));
	name()->setText(artist->name());

	// display tracks in the QScrollArea
	QList<Track *> tracks = rm.getTracksByArtist(mArtistId);
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

		auto *trackButton = new EntityListButton(track);
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

void SingleArtistPage::loadArtist(ArtistId artistId) {
	if (artistId == mArtistId) {
		return;
	}

	mArtistId = artistId;

	clearList();
	fillList();
}

ArtistId SingleArtistPage::artistId() const { return mArtistId; }

const char *SingleArtistPage::scrollListName() const { return "tracklist"; }

QLabel *SingleArtistPage::cover() {
	if (mCover == nullptr) {
		mCover = findChild<QLabel *>("artistCoverLabel");
	}

	return mCover;
}

QLabel *SingleArtistPage::name() {
	if (mName == nullptr) {
		mName = findChild<QLabel *>("artistNameLabel");
	}

	return mName;
}

QPushButton *SingleArtistPage::albumButton() {
	if (mAlbumButton == nullptr) {
		mAlbumButton = findChild<QPushButton *>("viewAlbumButton");
	}

	return mAlbumButton;
}
