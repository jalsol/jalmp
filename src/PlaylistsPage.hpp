#ifndef PLAYLISTSPAGE_HPP
#define PLAYLISTSPAGE_HPP

#include "Page.hpp"
#include "Types.hpp"

class PlaylistsPage : public Page {
public:
	PlaylistsPage(QWidget *parent = nullptr);
	void fillList() override;
	void loadArtistPlaylists(ArtistId artistId);

private:
	const char *scrollListName() const override;

	ArtistId mArtistId = 0;
};

#endif // PLAYLISTSPAGE_HPP
