#ifndef HOMEPAGE_HPP
#define HOMEPAGE_HPP

#include "Page.hpp"
#include "ScrollListCapture.hpp"
#include "Track.hpp"

#include <QQueue>

class QueueListCapture : public ScrollListCapture {
public:
	QueueListCapture(QWidget *parent = nullptr);
	QueueListCapture(int queueType, const QString &capture,
					 QWidget *parent = nullptr);

	void loadQueue(const QQueue<Track *> &queue);

private:
	void fill() override;

	QQueue<Track *> mQueue;
	int mQueueType;
};

class FavoriteListCapture : public ScrollListCapture {
public:
	FavoriteListCapture(QWidget *parent = nullptr);
	FavoriteListCapture(const QString &capture, QWidget *parent = nullptr);

	void loadFavorites();

private:
	void fill() override;

	QList<Track *> mFavorites;
};

class HomePage : public Page {
public:
	HomePage(QWidget *parent = nullptr);

	void fillQueues();
	void fillQueue(QueueType queueType);
	void fillFavorites();

public slots:
	void onTrackFavoriteChanged(TrackId trackId, bool favorite);

private:
	FavoriteListCapture mFavoriteList =
		FavoriteListCapture("favoritesList", this);

	QueueListCapture mQueueList[2] = {
		QueueListCapture(QueueType::User, "userQueueList", this),
		QueueListCapture(QueueType::System, "systemQueueList", this),
	};
};

#endif // HOMEPAGE_HPP
