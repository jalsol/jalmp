#include "MediaQueue.hpp"

#include "ResourceManager.hpp"

MediaQueue& MediaQueue::instance() {
	static MediaQueue instance;
	return instance;
}

void MediaQueue::setPlaylist(PlaylistId playlistId) {
	if (mPlaylistId != playlistId) {
		ResourceManager& rm = ResourceManager::instance();
		mPlaylistId = playlistId;
		mLoopingPlaylist = rm.getTracksByPlaylist(mPlaylistId);
	}

	mLastLoopingIdx = mLoopingPlaylist.size() - 1;
	mSystemQueue.clear();
	mSystemQueue.append(mLoopingPlaylist);
}

void MediaQueue::setPlaylist(const QList<Track*>& playlist) {
	mPlaylistId = PlaylistId::Invalid;
	mLoopingPlaylist.clear();
	mLoopingPlaylist.append(playlist);
	mLastLoopingIdx = mLoopingPlaylist.size() - 1;

	mSystemQueue.clear();
	mSystemQueue.append(mLoopingPlaylist);
}

void MediaQueue::addTrack(TrackId trackId) {
	ResourceManager& rm = ResourceManager::instance();
	Track* track = rm.getTrack(trackId);
	mUserQueue.append(track);
}

void MediaQueue::removeFromUser(TrackId trackId) {
	for (auto it = mUserQueue.begin(); it != mUserQueue.end(); ++it) {
		if ((*it)->id() == trackId) {
			mUserQueue.erase(it);
			break;
		}
	}
}

void MediaQueue::removeFromSystem(TrackId trackId) {
	for (auto it = mSystemQueue.begin(); it != mSystemQueue.end(); ++it) {
		if ((*it)->id() == trackId) {
			mSystemQueue.erase(it);
			break;
		}
	}
}

void MediaQueue::refillSystemQueue() {
	while (mSystemQueue.size() < mLoopingPlaylist.size()) {
		mLastLoopingIdx = (mLastLoopingIdx + 1) % mLoopingPlaylist.size();
		mSystemQueue.append(mLoopingPlaylist[mLastLoopingIdx]);
	}
}

Track* MediaQueue::next() {
	if (!mUserQueue.empty()) {
		return mOnRepeat ? mUserQueue.first() : mUserQueue.takeFirst();
	}

	refillSystemQueue();
	return mOnRepeat ? mSystemQueue.first() : mSystemQueue.takeFirst();
}

Track* MediaQueue::skipUserUntil(TrackId trackId) {
	while (!mUserQueue.empty()) {
		Track* track = mUserQueue.first();
		if (track->id() == trackId) {
			return track;
		}

		mUserQueue.takeFirst();
	}

	return nullptr;
}

Track* MediaQueue::skipSystemUntil(TrackId trackId) {
	refillSystemQueue();

	while (!mSystemQueue.empty()) {
		Track* track = mSystemQueue.first();
		if (track->id() == trackId) {
			return track;
		}

		mSystemQueue.takeFirst();
	}

	return nullptr;
}
