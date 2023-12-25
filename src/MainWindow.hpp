#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "MediaPlayer.hpp"

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

	void update();

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
};
#endif // MAINWINDOW_HPP
