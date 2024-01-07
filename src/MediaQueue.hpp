#ifndef MEDIAQUEUE_HPP
#define MEDIAQUEUE_HPP

#include "Track.hpp"
#include "Types.hpp"

#include <QQueue>

class MediaQueue {
public:
	static MediaQueue& instance();

	MediaQueue(const MediaQueue&) = delete;
	MediaQueue& operator=(const MediaQueue&) = delete;
	MediaQueue(MediaQueue&&) = delete;
	MediaQueue& operator=(MediaQueue&&) = delete;

	void setPlaylist(PlaylistId playlistId);
	void setPlaylist(const QList<Track*>& playlist);
	void addTrack(TrackId trackId);
	void removeFromUser(TrackId trackId);
	void removeFromSystem(TrackId trackId);
	void refillSystemQueue();

	Track* next();
	Track* skipUserUntil(TrackId trackId);
	Track* skipSystemUntil(TrackId trackId);

private:
	MediaQueue() = default;

	QQueue<Track*> mUserQueue;
	QQueue<Track*> mSystemQueue;

	QList<Track*> mLoopingPlaylist;
	int mLastLoopingIdx;
	PlaylistId mPlaylistId = PlaylistId::Invalid;

	bool mOnRepeat;
};

#endif // MEDIAQUEUE_HPP
