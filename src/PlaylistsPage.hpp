#ifndef PLAYLISTSPAGE_HPP
#define PLAYLISTSPAGE_HPP

#include "Page.hpp"
#include "ScrollListCapture.hpp"
#include "Types.hpp"

class PlaylistsListCapture : public ScrollListCapture {
public:
	PlaylistsListCapture(QWidget *parent = nullptr);
	PlaylistsListCapture(const QString &capture, QWidget *parent = nullptr);

	void loadArtistPlaylists(ArtistId artistId);

private:
	void fill() override;
	ArtistId mArtistId = 0;
};

class PlaylistsPage : public Page {
public:
	PlaylistsPage(QWidget *parent = nullptr);
	void fill(ArtistId artistId);

private:
	PlaylistsListCapture mList =
		PlaylistsListCapture("playlistsScrollList", this);
};

#endif // PLAYLISTSPAGE_HPP
