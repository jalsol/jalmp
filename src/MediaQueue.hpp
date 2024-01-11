#ifndef MEDIAQUEUE_HPP
#define MEDIAQUEUE_HPP

#include "Track.hpp"
#include "Types.hpp"

#include <QObject>
#include <QPair>
#include <QQueue>

class MediaQueue : public QObject {
	Q_OBJECT
public:
	static MediaQueue& instance();

	MediaQueue(const MediaQueue&) = delete;
	MediaQueue& operator=(const MediaQueue&) = delete;
	MediaQueue(MediaQueue&&) = delete;
	MediaQueue& operator=(MediaQueue&&) = delete;

	QQueue<Track*> queue(QueueType queueType) const;
	PlaylistId playlistId() const;

	void setPlaylist(PlaylistId playlistId);
	void setPlaylist(PlaylistId playlistId, const QList<Track*>& playlist);
	void addTrack(TrackId trackId);
	void addTrackAt(TrackId trackId, int index);
	QPair<Track*, int> removeFromQueue(QueueType queueType, TrackId trackId);
	void moveUp(QueueType queueType, TrackId trackId);
	void moveDown(QueueType queueType, TrackId trackId);
	void refillSystemQueue();
	void shuffleSystemQueue();
	void unshuffleSystemQueue();

	Track* next();
	Track* prev();
	Track* skipUntil(QueueType queueType, TrackId trackId);
	Track* skipPast(QueueType queueType, TrackId trackId);

signals:
	void queueChanged(QueueType queueType);

private:
	MediaQueue();

	QQueue<Track*> mQueue[2];
	QList<Track*> mHistory;

	QList<Track*> mLoopingPlaylist;
	int mLastLoopingIdx;
	PlaylistId mPlaylistId = PlaylistId::Invalid;

	bool mOnRepeat;
};

#endif // MEDIAQUEUE_HPP
