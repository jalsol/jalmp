#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include "MediaSlider.hpp"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	player->init(this);

	coverArt.load("../../assets/cover/2.jpg");
	ui->coverLabel->setPixmap(coverArt.scaled(ui->coverLabel->size()));

	connect(updater, SIGNAL(timeout()), this, SLOT(update()));

	connect(ui->playButton, &QPushButton::clicked, this,
			&MainWindow::onPlayButtonClicked);

	connect(ui->seekbar, &MediaSlider::sliderPressed, updater, &QTimer::stop);
	connect(ui->seekbar, &MediaSlider::sliderReleased, this,
			&MainWindow::onSeekbarReleased);

	connect(ui->volume, &MediaSlider::valueChanged, this,
			&MainWindow::onVolumeValueChanged);
	connect(ui->volume, &MediaSlider::sliderPressed, player,
			&MediaPlayer::cacheVolume);

	connect(ui->muteButton, &QPushButton::clicked, player,
			&MediaPlayer::toggleMuteVolume);

	connect(ui->repeatButton, &QPushButton::clicked, this,
			&MainWindow::onRepeatButtonClicked);

	connect(ui->homeButton, &QPushButton::clicked, this,
			&MainWindow::onHomeButtonClicked);
	connect(ui->searchButton, &QPushButton::clicked, this,
			&MainWindow::onSearchButtonClicked);
	connect(ui->playlistsButton, &QPushButton::clicked, this,
			&MainWindow::onPlaylistsButtonClicked);
	connect(ui->artistsButton, &QPushButton::clicked, this,
			&MainWindow::onArtistsButtonClicked);
	connect(ui->sidebarTitle, &SidebarTitle::linkActivated, this,
			&MainWindow::onSidebarTitleLinkActivated);

	// connect(ui->searchInput, &QLineEdit::textChanged, ui->searchPage,
	// 		&SearchPage::onSearchTextChanged);
	connect(ui->searchGoButton, &QPushButton::clicked, ui->searchPage,
			&SearchPage::onSearchButtonClicked);
	connect(ui->searchInput, &QLineEdit::returnPressed, ui->searchPage,
			&SearchPage::onSearchButtonClicked);
}

MainWindow::~MainWindow() {
	delete updater;
	delete ui;
}

void MainWindow::onPlayButtonClicked() {
	auto state = player->playbackState();

	if (state == QMediaPlayer::PlayingState) {
		player->pause();
		ui->playButton->setText("|>");
	} else {
		player->play();
		ui->playButton->setText("||");
		updater->start();
	}
}

void MainWindow::onSeekbarReleased() {
	QPoint relativeMousePos = ui->seekbar->mapFromGlobal(QCursor::pos());

	const float scale = static_cast<float>(player->duration());
	const auto newValue = static_cast<qint64>(scale / ui->seekbar->maximum()
											  * relativeMousePos.x());

	player->setPosition(newValue);
	updater->start();
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

void MainWindow::onHomeButtonClicked() {
	ui->stackedWidget->setCurrentIndex(Home);
}

void MainWindow::onSearchButtonClicked() {
	ui->stackedWidget->setCurrentIndex(Search);
}

void MainWindow::onPlaylistsButtonClicked() {
	ui->stackedWidget->setCurrentIndex(Playlists);
}

void MainWindow::onArtistsButtonClicked() {
	ui->stackedWidget->setCurrentIndex(Artists);
}

void MainWindow::onSidebarTitleLinkActivated(const QString &link) {
	if (link.startsWith("artist")) {
		ArtistId artistId{link.section('/', 1).toLongLong()};
		ui->singleArtistPage->loadArtist(artistId);
		ui->stackedWidget->setCurrentIndex(SingleArtist);
		resetCheckSidebarButtons();
	} else if (link.startsWith("track")) {
		onHomeButtonClicked();
		int64_t trackId{link.section('/', 1).toLongLong()};
		qDebug() << "track:" << trackId;
	}
}

void MainWindow::resetCheckSidebarButtons() {
	QVBoxLayout *sidebarButtons = ui->sidebarButtons;

	for (int i = 0; i < sidebarButtons->count(); ++i) {
		QAbstractButton *button = qobject_cast<QAbstractButton *>(
			sidebarButtons->itemAt(i)->widget());

		if (button) {
			// setAutoExclusive(false) is required to uncheck the button
			button->setAutoExclusive(false);
			button->setChecked(false);
			button->setAutoExclusive(true);
		}
	}
}

void MainWindow::update() {
	if (player->playbackState() != QMediaPlayer::PlayingState) {
		return;
	}

	const float scale = static_cast<float>(ui->seekbar->maximum());
	qint64 newValue =
		static_cast<qint64>(scale / player->duration() * player->position());

	if (newValue + 1 == ui->seekbar->maximum()) {
		newValue = 0;
		if (player->loops() == QMediaPlayer::Once) {
			player->pause();
			ui->playButton->setText("|>");
		}
	}

	ui->seekbar->setValue(newValue);
}
