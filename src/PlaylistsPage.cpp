#include "PlaylistsPage.hpp"

#include "EntityGridButton.hpp"
#include "ResourceManager.hpp"

#include <QGridLayout>

PlaylistsListCapture::PlaylistsListCapture(QWidget *parent)
	: ScrollListCapture{parent} {}

PlaylistsListCapture::PlaylistsListCapture(const QString &capture,
										   QWidget *parent)
	: ScrollListCapture{capture, parent} {}

void PlaylistsListCapture::loadArtistPlaylists(ArtistId artistId) {
	if (mArtistId == artistId) {
		return;
	}

	mArtistId = artistId;
	reload();
}

void PlaylistsListCapture::fill() {
	ResourceManager &rm = ResourceManager::instance();
	QList<Playlist *> playlists;
	if (mArtistId == ArtistId::Invalid) {
		playlists = rm.getAllPlaylists();
	} else {
		playlists = rm.getPlaylistsByArtist(mArtistId);
	}

	QGridLayout *layout = new QGridLayout{get()};
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 4; ++col) {
		layout->setColumnStretch(col, 1);
	}

	for (int i = 0; i < playlists.size(); ++i) {
		auto *playlistButton = new EntityGridButton(playlists[i]);
		layout->addWidget(playlistButton, i / 4, i % 4, Qt::AlignTop);
	}

	if (playlists.size() > 0) {
		layout->setRowStretch(playlists.size() / 4, 1);
	}

	get()->setLayout(layout);
}

PlaylistsPage::PlaylistsPage(QWidget *parent) : Page(parent) {}

void PlaylistsPage::fill(ArtistId artistId) {
	mList.loadArtistPlaylists(artistId);
}
