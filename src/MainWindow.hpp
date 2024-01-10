#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "MediaPlayer.hpp"
#include "Navigator.hpp"

#include <QMainWindow>
#include <QPixmap>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void onPlayButtonClicked();
	void onSeekbarReleased();
	void onVolumeValueChanged(int value);
	void onRepeatButtonClicked();
	void onShuffleButtonClicked();
	void onStopButtonClicked();
	void onMuteButtonClicked();

	void onHomeButtonClicked();
	void onSearchButtonClicked();
	void onPlaylistsButtonClicked();
	void onArtistsButtonClicked();
	void onViewOriginButtonClicked();

	void onSidebarTitleLinkActivated(const QString &link);

	void onNavigatedToArtist(ArtistId artistId);
	void onNavigatedToPlaylist(PlaylistId playlistId);
	void onNavigatedToTrack(PlaylistId playlistId, TrackId trackId);
	void onNavigatedToHome();
	void onNavigatedToSearch();

	void update();
	void playTrack(Track *track);

private:
	enum PageId {
		Home,
		Search,
		Playlists,
		Artists,
		Tracklist,
	};

	Ui::MainWindow *ui;

	MediaPlayer *player = MediaPlayer::instance();
	QTimer *updater = new QTimer(this);

	QPixmap coverArt;

	Navigator *navigator = Navigator::instance();
};
#endif // MAINWINDOW_HPP
