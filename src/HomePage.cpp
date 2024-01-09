#include "HomePage.hpp"

#include "EntityListButton.hpp"
#include "FavoriteButton.hpp"
#include "MediaQueue.hpp"
#include "ResourceManager.hpp"

#include <QGridLayout>
#include <QLabel>

QueueListCapture::QueueListCapture(QWidget *parent)
	: ScrollListCapture(parent) {}

QueueListCapture::QueueListCapture(const QString &capture, QWidget *parent)
	: ScrollListCapture(capture, parent) {}

void QueueListCapture::loadQueue(const QQueue<Track *> &queue) {
	mQueue = queue;
	reload();
}

void QueueListCapture::fill() {
	QGridLayout *layout = new QGridLayout(get());
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 7; ++col) {
		layout->setColumnStretch(col, 1);
	}

	int row = 0;
	for (Track *track : mQueue) {
		{
			auto *idLabel = new QLabel();
			idLabel->setText(QString::number(row + 1));
			idLabel->setFixedSize(20, 50);
			idLabel->setAlignment(Qt::AlignCenter);
			layout->addWidget(idLabel, row, 0, Qt::AlignTop);
		}

		{
			auto *durationLabel = new QLabel();
			durationLabel->setText(track->duration().toString("mm:ss"));
			durationLabel->setFixedSize(50, 50);
			durationLabel->setAlignment(Qt::AlignCenter);
			layout->addWidget(durationLabel, row, 1, Qt::AlignTop);
		}

		{
			auto *button = new EntityListButton(track);
			layout->addWidget(button, row, 2, Qt::AlignTop);
		}

		{
			auto *favoriteButton =
				new FavoriteButton((qint64)track->id(), track->isFavorite());
			layout->addWidget(favoriteButton, row, 3, Qt::AlignTop);
		}

		{
			auto *deleteButton = new QPushButton();
			deleteButton->setText("Del");
			deleteButton->setFixedSize(50, 50);
			layout->addWidget(deleteButton, row, 4, Qt::AlignTop);
		}

		{
			auto *upButton = new QPushButton();
			upButton->setText("Up");
			upButton->setFixedSize(50, 50);
			layout->addWidget(upButton, row, 5, Qt::AlignTop);
		}

		{
			auto *downButton = new QPushButton();
			downButton->setText("Down");
			downButton->setFixedSize(50, 50);
			layout->addWidget(downButton, row, 6, Qt::AlignTop);
		}

		++row;
	}

	if (row > 0) {
		layout->setRowStretch(row - 1, 1);
	}

	get()->setLayout(layout);
}

FavoriteListCapture::FavoriteListCapture(QWidget *parent)
	: ScrollListCapture(parent) {}

FavoriteListCapture::FavoriteListCapture(const QString &capture,
										 QWidget *parent)
	: ScrollListCapture(capture, parent) {}

void FavoriteListCapture::loadFavorites() {
	qDebug() << "loading favorites";
	ResourceManager &rm = ResourceManager::instance();
	mFavorites = rm.getAllFavoriteTracks();
	MediaQueue::instance().setPlaylist(mFavorites);
	reload();
}

void FavoriteListCapture::fill() {
	QGridLayout *layout = new QGridLayout(get());
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 4; ++col) {
		layout->setColumnStretch(col, 1);
	}

	int row = 0;
	for (auto *track : mFavorites) {
		int col = 0;

		{
			auto *idLabel = new QLabel();
			idLabel->setText(QString::number(row + 1));
			idLabel->setFixedSize(20, 50);
			idLabel->setAlignment(Qt::AlignCenter);
			layout->addWidget(idLabel, row, col++, Qt::AlignTop);
		}

		{
			auto *durationLabel = new QLabel();
			durationLabel->setText(track->duration().toString("mm:ss"));
			durationLabel->setFixedSize(50, 50);
			durationLabel->setAlignment(Qt::AlignCenter);
			layout->addWidget(durationLabel, row, col++, Qt::AlignTop);
		}

		{
			EntityListButton *trackButton = new EntityListButton(track);
			layout->addWidget(trackButton, row, col++, Qt::AlignTop);
		}

		{
			auto *favoriteButton =
				new FavoriteButton((qint64)track->id(), track->isFavorite());
			layout->addWidget(favoriteButton, row, col++, Qt::AlignTop);
		}

		++row;
	}

	if (row > 0) {
		layout->setRowStretch(row - 1, 1);
	}

	// set the scroll area's widget
	get()->setLayout(layout);
}

HomePage::HomePage(QWidget *parent) : Page(parent) {}

void HomePage::fillQueues() {
	MediaQueue &queue = MediaQueue::instance();
	mUserQueueList.loadQueue(queue.userQueue());
	mSystemQueueList.loadQueue(queue.systemQueue());
}

void HomePage::fillFavorites() { mFavoriteList.loadFavorites(); }
