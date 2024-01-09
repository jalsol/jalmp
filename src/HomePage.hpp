#ifndef HOMEPAGE_HPP
#define HOMEPAGE_HPP

#include "Page.hpp"
#include "ScrollListCapture.hpp"
#include "Track.hpp"

#include <QQueue>

class QueueListCapture : public ScrollListCapture {
public:
	QueueListCapture(QWidget *parent = nullptr);
	QueueListCapture(const QString &capture, QWidget *parent = nullptr);

	void loadQueue(const QQueue<Track *> &queue);

private:
	void fill() override;

	QQueue<Track *> mQueue;
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
	void fillFavorites();

private:
	FavoriteListCapture mFavoriteList =
		FavoriteListCapture("favoritesList", this);
	QueueListCapture mUserQueueList = QueueListCapture("userQueueList", this);
	QueueListCapture mSystemQueueList =
		QueueListCapture("systemQueueList", this);
};

#endif // HOMEPAGE_HPP
