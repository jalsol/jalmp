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

	void onHomeButtonClicked();
	void onSearchButtonClicked();
	void onPlaylistsButtonClicked();
	void onArtistsButtonClicked();

	void onSidebarTitleLinkActivated(const QString &link);
	void resetCheckSidebarButtons();

	void onNavigatedToArtist(ArtistId artistId);
	void onNavigatedToPlaylist(PlaylistId playlistId);
	void onNavigatedToTrack(PlaylistId playlistId, TrackId trackId);

	void update();
	void playTrack(Track *track);

private:
	enum PageId {
		Home,
		Search,
		Playlists,
		Artists,
		SingleArtist,
	};

	Ui::MainWindow *ui;

	MediaPlayer *player = MediaPlayer::instance();
	QTimer *updater = new QTimer(this);

	QPixmap coverArt;

	Navigator *navigator = Navigator::instance();
};
#endif // MAINWINDOW_HPP
