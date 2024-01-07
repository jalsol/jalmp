#ifndef NAVIGATOR_HPP
#define NAVIGATOR_HPP

#include "Types.hpp"

#include <QObject>
#include <QString>

class Navigator : public QObject {
	Q_OBJECT
public:
	static Navigator* instance();

	Navigator(const Navigator&) = delete;
	Navigator& operator=(const Navigator&) = delete;
	Navigator(Navigator&&) = delete;
	Navigator& operator=(Navigator&&) = delete;

	void navigateTo(QString path);

signals:
	void navigatedToArtist(ArtistId artistId);
	void navigatedToPlaylist(PlaylistId playlistId);
	void navigatedToTrack(PlaylistId playlistId, TrackId trackId);

private:
	Navigator() = default;
};

#endif // NAVIGATOR_HPP
