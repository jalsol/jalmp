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
			auto *button = new EntityListButton(track);
			layout->addWidget(button, row, col++, Qt::AlignTop);
		}

		{
			auto *favoriteButton =
				new FavoriteButton((qint64)track->id(), track->isFavorite());
			layout->addWidget(favoriteButton, row, col++, Qt::AlignTop);
		}

		{
			auto *deleteButton = new DeleteQueueButton((qint64)track->id());
			layout->addWidget(deleteButton, row, col++, Qt::AlignTop);
		}

		{
			auto *upButton = new UpQueueButton((qint64)track->id());
			layout->addWidget(upButton, row, col++, Qt::AlignTop);
		}

		{
			auto *downButton = new DownQueueButton((qint64)track->id());
			layout->addWidget(downButton, row, col++, Qt::AlignTop);
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
			auto *idLabel = new IndexLabel(row + 1);
			layout->addWidget(idLabel, row, col++, Qt::AlignTop);
		}

		{
			auto *durationLabel = new DurationLabel(track->duration());
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

HomePage::HomePage(QWidget *parent) : Page(parent) {}

void HomePage::fillQueues() {
	MediaQueue &queue = MediaQueue::instance();
	mUserQueueList.loadQueue(queue.userQueue());
	mSystemQueueList.loadQueue(queue.systemQueue());
}

void HomePage::fillFavorites() { mFavoriteList.loadFavorites(); }
