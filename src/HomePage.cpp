#include "HomePage.hpp"

#include "AddQueueButton.hpp"
#include "DeleteQueueButton.hpp"
#include "DownQueueButton.hpp"
#include "DurationLabel.hpp"
#include "EntityListButton.hpp"
#include "FavoriteButton.hpp"
#include "IndexLabel.hpp"
#include "MediaQueue.hpp"
#include "ResourceManager.hpp"
#include "UpQueueButton.hpp"

#include <QGridLayout>
#include <QLabel>

QueueListCapture::QueueListCapture(QWidget *parent)
	: ScrollListCapture(parent) {}

QueueListCapture::QueueListCapture(int queueType, const QString &capture,
								   QWidget *parent)
	: ScrollListCapture(capture, parent), mQueueType(queueType) {}

void QueueListCapture::loadQueue(const QQueue<Track *> &queue) {
	mQueue = queue;
	reload();
}

void QueueListCapture::fill() {
	QGridLayout *layout = new QGridLayout(get());
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 8; ++col) {
		layout->setColumnStretch(col, 1);
	}

	int row = 0;
	for (Track *track : mQueue) {
		int col = 0;

		{
			auto *idLabel = new IndexLabel(row + 1);
			layout->addWidget(idLabel, row, col++, Qt::AlignTop);
		}

		{
			auto *durationLabel = new DurationLabel(track->duration());
			layout->addWidget(durationLabel, row, col++, Qt::AlignTop);
		}

		{
			qint64 playlistId =
				(mQueueType == QueueType::User)
					? PlaylistId::UserQueue
					: (qint64)MediaQueue::instance().playlistId();

			auto *button = new EntityListButton(track, playlistId);
			layout->addWidget(button, row, col++, Qt::AlignTop);
		}

		{
			auto *favoriteButton =
				new FavoriteButton((qint64)track->id(), track->isFavorite());
			layout->addWidget(favoriteButton, row, col++, Qt::AlignTop);
		}

		{
			auto *deleteButton =
				new DeleteQueueButton(mQueueType, (qint64)track->id());
			layout->addWidget(deleteButton, row, col++, Qt::AlignTop);
		}

		{
			auto *upButton = new UpQueueButton(mQueueType, (qint64)track->id());
			layout->addWidget(upButton, row, col++, Qt::AlignTop);
		}

		{
			auto *downButton =
				new DownQueueButton(mQueueType, (qint64)track->id());
			layout->addWidget(downButton, row, col++, Qt::AlignTop);
		}

		{
			auto *addButton = new AddQueueButton((qint64)track->id());
			layout->addWidget(addButton, row, col++, Qt::AlignTop);
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
			auto *idLabel = new IndexLabel(row + 1);
			layout->addWidget(idLabel, row, col++, Qt::AlignTop);
		}

		{
			auto *durationLabel = new DurationLabel(track->duration());
			layout->addWidget(durationLabel, row, col++, Qt::AlignTop);
		}

		{
			EntityListButton *trackButton =
				new EntityListButton(track, PlaylistId::Favorites);
			layout->addWidget(trackButton, row, col++, Qt::AlignTop);
		}

		{
			auto *favoriteButton =
				new FavoriteButton((qint64)track->id(), track->isFavorite());
			layout->addWidget(favoriteButton, row, col++, Qt::AlignTop);
		}

		{
			auto *addQueueButton = new AddQueueButton((qint64)track->id());
			layout->addWidget(addQueueButton, row, col++, Qt::AlignTop);
		}

		++row;
	}

	if (row > 0) {
		layout->setRowStretch(row - 1, 1);
	}

	// set the scroll area's widget
	get()->setLayout(layout);
}

HomePage::HomePage(QWidget *parent) : Page(parent) {
	connect(&MediaQueue::instance(), &MediaQueue::queueChanged, this,
			&HomePage::fillQueue);
	connect(&ResourceManager::instance(),
			&ResourceManager::trackFavoriteChanged, this,
			&HomePage::onTrackFavoriteChanged);
}

void HomePage::fillQueues() {
	fillQueue(QueueType::User);
	fillQueue(QueueType::System);
}

void HomePage::fillQueue(QueueType queueType) {
	MediaQueue &queue = MediaQueue::instance();
	mQueueList[queueType].loadQueue(queue.queue(queueType));
}

void HomePage::fillFavorites() { mFavoriteList.loadFavorites(); }

void HomePage::onTrackFavoriteChanged(TrackId trackId, bool isFavorite) {
	fillFavorites();
	fillQueue(QueueType::User);

	MediaQueue &queue = MediaQueue::instance();
	if (queue.playlistId() == PlaylistId::Favorites) {
		queue.removeFromQueue(QueueType::System, trackId);
	} else {
		fillQueue(QueueType::System);
	}
}
