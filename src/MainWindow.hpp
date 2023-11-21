#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QAudioOutput>
#include <QMainWindow>
#include <QMediaPlayer>
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
	void onSeekbarPressed();
	void onSeekbarReleased();
	void onVolumeValueChanged(int value);
	void onMuteButtonClicked();
	void onVolumePressed();
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
	QMediaPlayer *player = new QMediaPlayer(this);
	QAudioOutput *audioOutput = new QAudioOutput();
	QTimer *updater = new QTimer(this);
};
#endif // MAINWINDOW_HPP
