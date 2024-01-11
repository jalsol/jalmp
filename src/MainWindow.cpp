#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include "FavoriteButton.hpp"
#include "MediaQueue.hpp"
#include "MediaSlider.hpp"
#include "ResourceManager.hpp"

#include <QDebug>
#include <QPixmap>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	player->init(this);
	updater->setInterval(500);

	connect(updater, SIGNAL(timeout()), this, SLOT(update()));

	connect(ui->playButton, &QPushButton::clicked, this,
			&MainWindow::onPlayButtonClicked);

	connect(ui->seekbar, &MediaSlider::sliderPressed, updater, &QTimer::stop);
	connect(ui->seekbar, &MediaSlider::sliderReleased, this,
			&MainWindow::onSeekbarReleased);
	connect(ui->seekbar, &MediaSlider::valueChanged, this,
			&MainWindow::onSeekbarValueChanged);

	connect(ui->volume, &MediaSlider::valueChanged, this,
			&MainWindow::onVolumeValueChanged);
	connect(ui->volume, &MediaSlider::sliderPressed, player,
			&MediaPlayer::cacheVolume);

	connect(ui->muteButton, &QPushButton::clicked, this,
			&MainWindow::onMuteButtonClicked);

	connect(ui->repeatButton, &QPushButton::clicked, this,
			&MainWindow::onRepeatButtonClicked);
	connect(ui->shuffleButton, &QPushButton::clicked, this,
			&MainWindow::onShuffleButtonClicked);
	connect(ui->stopButton, &QPushButton::clicked, this,
			&MainWindow::onStopButtonClicked);
	connect(ui->nextButton, &QPushButton::clicked, this,
			&MainWindow::onNextButtonClicked);
	connect(ui->prevButton, &QPushButton::clicked, this,
			&MainWindow::onPrevButtonClicked);

	connect(ui->homeButton, &QPushButton::clicked, this,
			&MainWindow::onHomeButtonClicked);
	connect(ui->searchButton, &QPushButton::clicked, this,
			&MainWindow::onSearchButtonClicked);
	connect(ui->playlistsButton, &QPushButton::clicked, this,
			&MainWindow::onPlaylistsButtonClicked);
	connect(ui->artistsButton, &QPushButton::clicked, this,
			&MainWindow::onArtistsButtonClicked);
	connect(ui->sidebarTitle, &SidebarTitle::linkActivated, navigator,
			&Navigator::navigateTo);
	connect(ui->lyricsButton, &QPushButton::clicked, this,
			&MainWindow::onLyricsButtonClicked);

	connect(ui->searchGoButton, &QPushButton::clicked, ui->searchPage,
			&SearchPage::onSearchButtonClicked);
	connect(ui->searchInput, &QLineEdit::returnPressed, ui->searchPage,
			&SearchPage::onSearchButtonClicked);

	connect(navigator, &Navigator::navigatedToArtist, this,
			&MainWindow::onNavigatedToArtist);
	connect(navigator, &Navigator::navigatedToPlaylist, this,
			&MainWindow::onNavigatedToPlaylist);
	connect(navigator, &Navigator::navigatedToTrack, this,
			&MainWindow::onNavigatedToTrack);
	connect(navigator, &Navigator::navigatedToHome, this,
			&MainWindow::onNavigatedToHome);
	connect(navigator, &Navigator::navigatedToSearch, this,
			&MainWindow::onNavigatedToSearch);

	connect(ui->viewTracklistOriginButton, &QPushButton::clicked, this,
			&MainWindow::onViewOriginButtonClicked);

	{
		ui->homePage->fillFavorites();
		ui->background->setStyleSheet(
			"QLabel { background-image: url(../../assets/background.jpeg); }");

		ui->coverLabel->setPixmap(QPixmap("../../assets/placeholder.png"));

		ui->searchGoButton->setIcon(QPixmap("../../assets/24D500.png"));
		ui->searchGoButton->setIconSize(QSize(30, 30));

		ui->sidebarFavButton->setVisible(false);

		ui->iconLabel->setPixmap(QPixmap("../../assets/53D058.png"));
		ui->iconLabel->setScaledContents(true);
	}

	{
		ui->playButton->setOnTexture("4C7750");
		ui->playButton->setOffTexture("4C9F00");
		ui->muteButton->setOnTexture("4B8068");
		ui->muteButton->setOffTexture("4B9660");
		ui->repeatButton->setOnTexture("1D2E78");
		ui->repeatButton->setOffTexture("1D3C68");
		ui->shuffleButton->setOnTexture("1D1518");
		ui->shuffleButton->setOffTexture("1D2230");
	}
	{
		auto *Space = new QShortcut(QKeySequence(Qt::Key_Space), this);
		auto *N = new QShortcut(QKeySequence(Qt::Key_N), this);
		auto *P = new QShortcut(QKeySequence(Qt::Key_P), this);
		auto *M = new QShortcut(QKeySequence(Qt::Key_M), this);
		auto *R = new QShortcut(QKeySequence(Qt::Key_R), this);
		auto *CtrlR = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_R), this);

		connect(Space, &QShortcut::activated, this,
				&MainWindow::onPlayButtonClicked);
		connect(N, &QShortcut::activated, this,
				&MainWindow::onNextButtonClicked);
		connect(P, &QShortcut::activated, this,
				&MainWindow::onPrevButtonClicked);
		connect(M, &QShortcut::activated, this,
				&MainWindow::onMuteButtonClicked);
		connect(R, &QShortcut::activated, this,
				&MainWindow::onRepeatButtonClicked);
		connect(CtrlR, &QShortcut::activated, this,
				&MainWindow::onShuffleButtonClicked);
	}
}

MainWindow::~MainWindow() {
	delete updater;
	delete ui;

	QFile::remove("../../audio.mp3");
	QFile::remove("../../lyrics.txt");
}

void MainWindow::onPlayButtonClicked() {
	auto state = player->playbackState();
	if (player->source().isEmpty()) {
		Track *track = player->nextTrack();
		if (track != nullptr) {
			playTrack(track);
		} else {
			return;
		}
	}

	if (state == QMediaPlayer::PlayingState) {
		player->pause();
		ui->playButton->setChecked(false);
	} else {
		player->play();
		ui->playButton->setChecked(true);
		updater->start();
	}
}

void MainWindow::onSeekbarReleased() {
	QPoint relativeMousePos = ui->seekbar->mapFromGlobal(QCursor::pos());

	const float scale = static_cast<float>(player->duration());
	const auto newValue = static_cast<qint64>(scale / ui->seekbar->maximum()
											  * relativeMousePos.x());

	player->setPosition(newValue);
	ui->currentTimeLabel->setDuration(player->position());
	updater->start();

	update();
}

void MainWindow::onSeekbarValueChanged(int value) {
	if (value == ui->seekbar->maximum()
		&& QGuiApplication::mouseButtons() != Qt::LeftButton) {
		value = 0;
	}

	const float scale = static_cast<float>(player->duration());
	const auto newValue =
		static_cast<qint64>(scale / ui->seekbar->maximum() * value);

	ui->seekbar->setValue(value);
	ui->currentTimeLabel->setDuration(newValue);
}

void MainWindow::onVolumeValueChanged(int value) {
	player->setVolume(value);
	if (player->isMuted()) {
		ui->muteButton->setChecked(true);
	} else {
		ui->muteButton->setChecked(false);
	}
}

void MainWindow::onRepeatButtonClicked() {
	if (player->isAvailable()) {
		const int loops = player->loops();

		if (loops == QMediaPlayer::Once) {
			player->setLoops(QMediaPlayer::Infinite);
			ui->repeatButton->setChecked(true);
		} else {
			player->setLoops(QMediaPlayer::Once);
			ui->repeatButton->setChecked(false);
		}
	}
}

void MainWindow::onShuffleButtonClicked() {
	if (ui->shuffleButton->isChecked()) {
		ui->shuffleButton->setChecked(true);
		MediaQueue::instance().shuffleSystemQueue();
	} else {
		ui->shuffleButton->setChecked(false);
		MediaQueue::instance().unshuffleSystemQueue();
	}
}

void MainWindow::onStopButtonClicked() {
	player->stop();
	updater->stop();
	ui->seekbar->setValue(0);
	ui->playButton->setChecked(false);
}

void MainWindow::onMuteButtonClicked() {
	player->toggleMuteVolume();

	if (player->isMuted()) {
		ui->volume->setValue(0);
		ui->muteButton->setChecked(true);
	} else {
		ui->volume->setValue(player->volume());
		ui->muteButton->setChecked(false);
	}
}

void MainWindow::onNextButtonClicked() {
	Track *track = player->nextTrack();
	if (track != nullptr) {
		playTrack(track);
	} else {
		ui->playButton->setChecked(false);
	}
}

void MainWindow::onPrevButtonClicked() {
	Track *track = player->prevTrack();
	if (track != nullptr) {
		playTrack(track);
	} else {
		ui->playButton->setChecked(false);
	}
}

void MainWindow::onHomeButtonClicked() {
	ui->stackedWidget->setCurrentIndex(Home);
}

void MainWindow::onSearchButtonClicked() {
	ui->stackedWidget->setCurrentIndex(Search);
}

void MainWindow::onPlaylistsButtonClicked() {
	ui->playlistsPage->fill(ArtistId::Invalid);
	ui->stackedWidget->setCurrentIndex(Playlists);
}

void MainWindow::onArtistsButtonClicked() {
	ui->artistsPage->fill();
	ui->stackedWidget->setCurrentIndex(Artists);
}

void MainWindow::onLyricsButtonClicked() {
	ui->stackedWidget->setCurrentIndex(Lyrics);
}

void MainWindow::onViewOriginButtonClicked() {
	auto [id, type] = ui->tracklistPage->id();

	if (type == EntityType::Artist) {
		ui->playlistsPage->fill((qint64)id);
		ui->stackedWidget->setCurrentIndex(Playlists);
	} else {
		Artist *artist =
			ResourceManager::instance().getArtistByPlaylist((qint64)id);
		onNavigatedToArtist((qint64)artist->id());
	}
}

void MainWindow::onNavigatedToArtist(ArtistId artistId) {
	ui->tracklistPage->fill(artistId, EntityType::Artist);
	ui->stackedWidget->setCurrentIndex(Tracklist);
	ui->viewTracklistOriginButton->setText("View Albums");
}

void MainWindow::onNavigatedToPlaylist(PlaylistId playlistId) {
	ui->tracklistPage->fill(playlistId, EntityType::Playlist);
	ui->stackedWidget->setCurrentIndex(Tracklist);
	ui->viewTracklistOriginButton->setText("View Artist");
}

void MainWindow::onNavigatedToTrack(PlaylistId playlistId, TrackId trackId) {
	Track *track = player->invokeTrack(playlistId, trackId);
	playTrack(track);
}

void MainWindow::onNavigatedToSearch() {
	ui->stackedWidget->setCurrentIndex(Search);
}

void MainWindow::onNavigatedToHome() {
	ui->stackedWidget->setCurrentIndex(Home);
}

void MainWindow::update() {
	const float scale = static_cast<float>(ui->seekbar->maximum());
	qint64 newValue =
		static_cast<qint64>(scale / player->duration() * player->position());

	if (newValue == ui->seekbar->maximum()) {
		newValue = 0;

		qDebug() << "next track";

		if (player->loops() == QMediaPlayer::Once) {
			qDebug() << "once";
			Track *track = player->nextTrack();
			if (track != nullptr) {
				playTrack(track);
				return;
			} else {
				player->stop();
				updater->stop();
			}
		}
	}

	onSeekbarValueChanged(newValue);
}

void MainWindow::playTrack(Track *track) {
	player->pause();
	ui->playButton->setChecked(false);

	ui->seekbar->setValue(0);

	// change cover art
	coverArt.load("../.." + track->cover());
	ui->coverLabel->setPixmap(coverArt.scaled(ui->coverLabel->size()));

	// change title
	ResourceManager &rm = ResourceManager::instance();
	QString trackPath =
		QString("playlist/%1").arg(QString::number(player->playlistId()));

	QList<Artist *> artists = rm.getArtistsByTrack(TrackId(track->id()));
	QString artistsAnchor =
		QString("<a href=\"artist/%1\">%2</a>")
			.arg(QString::number(artists[0]->id()), artists[0]->name());

	for (int i = 1; i < artists.size(); ++i) {
		artistsAnchor +=
			QString(", <a href=\"artist/%1\">%2</a>")
				.arg(QString::number(artists[i]->id()), artists[i]->name());
	}

	ui->sidebarTitle->setText(
		QString("<a href=\"%1\"><b>%2</b></a>"
				"<br />"
				"%3")
			.arg(trackPath, track->name(), artistsAnchor));

	onPlayButtonClicked();
	ui->homePage->fillQueues();

	ui->sidebarFavButton->setVisible(true);
	ui->sidebarFavButton->setTrackId((qint64)track->id());
	ui->sidebarFavButton->setFavorite(track->isFavorite());
	ui->totalTimeLabel->setDuration(track->duration());
}
