#include "SingleArtistPage.hpp"

#include "ResourceManager.hpp"

#include <QDebug>
#include <QLabel>
#include <QList>

SingleArtistPage::SingleArtistPage(QWidget *parent) : QWidget(parent) {}

void SingleArtistPage::loadArtist(ArtistId artistId) {
	ResourceManager &rm = ResourceManager::instance();
	Artist *artist = rm.getArtist(artistId);
	Q_ASSERT(artist != nullptr);

	auto *cover = findChild<QLabel *>("artistCoverLabel");
	auto *name = findChild<QLabel *>("artistNameLabel");

	// load cover and set name
	mPixmap.load("../../" + artist->cover());
	cover->setPixmap(mPixmap.scaled(200, 200, Qt::KeepAspectRatio,
									Qt::SmoothTransformation));
	name->setText(artist->name());

	// load tracks
	QList<Track *> tracks = rm.getTracksByArtist(artistId);
	for (auto *track : tracks) {
		qDebug() << track->title();
	}
}
