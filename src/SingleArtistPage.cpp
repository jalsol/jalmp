#include "SingleArtistPage.hpp"

#include "ResourceManager.hpp"
#include "TrackListButton.hpp"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QList>

SingleArtistPage::SingleArtistPage(QWidget *parent) : QWidget(parent) {}

void SingleArtistPage::loadArtist(ArtistId artistId) {
	if (artistId == mArtistId) {
		return;
	}

	mArtistId = artistId;
	clearList();

	ResourceManager &rm = ResourceManager::instance();
	Artist *artist = rm.getArtist(artistId);
	Q_ASSERT(artist != nullptr);

	// load cover and set name
	mPixmap.load("../../" + artist->cover());
	cover()->setPixmap(mPixmap.scaled(200, 200, Qt::KeepAspectRatio,
									  Qt::SmoothTransformation));
	name()->setText(artist->name());

	// display tracks in the QScrollArea
	QList<Track *> tracks = rm.getTracksByArtist(artistId);
	QGridLayout *layout = new QGridLayout{tracklist()};
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

		auto *likeButton = new QPushButton();
		// likeButton->setIcon(QIcon(":/icons/like.png"));
		likeButton->setText("Like");
		likeButton->setFixedSize(50, 50);
		layout->addWidget(likeButton, row, 1, Qt::AlignTop);

		auto *trackButton = new TrackListButton(track);
		layout->addWidget(trackButton, row, 2, Qt::AlignTop);

		auto *durationLabel = new QLabel();
		// qDebug() << track->duration().toString();
		durationLabel->setText(track->duration().toString("mm:ss"));
		durationLabel->setFixedSize(50, 50);
		durationLabel->setAlignment(Qt::AlignCenter);
		layout->addWidget(durationLabel, row, 3, Qt::AlignTop);

		++row;
	}

	layout->setRowStretch(row - 1, 1);

	// set the scroll area's widget
	tracklist()->setLayout(layout);
}

void SingleArtistPage::clearList() {
	QLayout *layout = tracklist()->layout();

	if (layout == nullptr) {
		return;
	}

	QLayoutItem *item;
	while ((item = layout->takeAt(0)) != nullptr) {
		delete item->widget();
		delete item;
	}
}

QWidget *SingleArtistPage::tracklist() {
	if (mTracklist == nullptr) {
		mTracklist = findChild<QWidget *>("tracklist");
	}

	return mTracklist;
}

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
