#include "MediaQueue.hpp"

#include "Navigator.hpp"
#include "ResourceManager.hpp"

MediaQueue& MediaQueue::instance() {
	static MediaQueue instance;
	return instance;
}

MediaQueue::MediaQueue() {
	auto nav = Navigator::instance();
	connect(nav, &Navigator::queueUp, this, &MediaQueue::moveUp);
	connect(nav, &Navigator::queueDown, this, &MediaQueue::moveDown);
	connect(nav, &Navigator::queueDeleted, this, &MediaQueue::removeFromQueue);
	connect(nav, &Navigator::queueAdded, this, &MediaQueue::addTrack);
}

QQueue<Track*> MediaQueue::queue(QueueType queueType) const {
	return mQueue[queueType];
}

PlaylistId MediaQueue::playlistId() const { return mPlaylistId; }

void MediaQueue::setPlaylist(PlaylistId playlistId) {
	if (mPlaylistId != playlistId) {
		ResourceManager& rm = ResourceManager::instance();
		mPlaylistId = playlistId;
		mLoopingPlaylist = rm.getTracksByPlaylist(mPlaylistId);
	}

	mLastLoopingIdx = mLoopingPlaylist.size() - 1;
	mQueue[System].clear();
	mQueue[System].append(mLoopingPlaylist);
	emit queueChanged(System);
}

void MediaQueue::setPlaylist(PlaylistId playlistId,
							 const QList<Track*>& playlist) {
	mPlaylistId = playlistId;
	mLoopingPlaylist.clear();
	mLoopingPlaylist.append(playlist);
	mLastLoopingIdx = mLoopingPlaylist.size() - 1;

	mQueue[System].clear();
	mQueue[System].append(mLoopingPlaylist);
	emit queueChanged(System);
}

void MediaQueue::addTrack(TrackId trackId) {
	addTrackAt(trackId, mQueue[User].size());
}

void MediaQueue::addTrackAt(TrackId trackId, int index) {
	ResourceManager& rm = ResourceManager::instance();
	Track* track = rm.getTrack(trackId);
	mQueue[User].insert(index, track);
	emit queueChanged(User);
}

QPair<Track*, int> MediaQueue::removeFromQueue(QueueType queueType,
											   TrackId trackId) {
	int idx = 0;
	auto& queue = mQueue[queueType];

	for (auto it = queue.begin(); it != queue.end(); ++it, ++idx) {
		if ((*it)->id() == trackId) {
			auto ret = qMakePair(*it, idx);
			queue.erase(it);
			emit queueChanged(queueType);
			return ret;
		}
	}

	return qMakePair(nullptr, -1);
}

void MediaQueue::moveUp(QueueType queueType, TrackId trackId) {
	auto [track, idx] = removeFromQueue(queueType, trackId);
	if (track) {
		mQueue[queueType].insert(idx - 1, track);
	}

	emit queueChanged(queueType);
}

void MediaQueue::moveDown(QueueType queueType, TrackId trackId) {
	auto [track, idx] = removeFromQueue(queueType, trackId);
	if (track) {
		mQueue[queueType].insert(idx + 1, track);
	}

	emit queueChanged(queueType);
}

void MediaQueue::refillSystemQueue() {
	while (mQueue[System].size() < mLoopingPlaylist.size()) {
		mLastLoopingIdx = (mLastLoopingIdx + 1) % mLoopingPlaylist.size();
		mQueue[System].append(mLoopingPlaylist[mLastLoopingIdx]);
	}

	emit queueChanged(System);
}

Track* MediaQueue::next() {
	if (!mQueue[User].empty()) {
		if (mOnRepeat) {
			return mQueue[User].first();
		} else {
			Track* track = mQueue[User].takeFirst();
			emit queueChanged(User);
			return track;
		}
	}

	refillSystemQueue();

	if (mQueue[System].empty()) {
		return nullptr;
	}

	if (mOnRepeat) {
		return mQueue[System].first();
	} else {
		Track* track = mQueue[System].takeFirst();
		emit queueChanged(System);
		return track;
	}
}

Track* MediaQueue::skipUntil(QueueType queueType, TrackId trackId) {
	while (!mQueue[queueType].empty()) {
		Track* track = mQueue[queueType].first();
		if (track->id() == trackId) {
			return track;
		}

		mQueue[queueType].takeFirst();
	}

	emit queueChanged(queueType);

	return nullptr;
}

Track* MediaQueue::skipPast(QueueType queueType, TrackId trackId) {
	while (!mQueue[queueType].empty()) {
		Track* track = mQueue[queueType].first();
		if (track->id() == trackId) {
			mQueue[queueType].takeFirst();
			emit queueChanged(queueType);
			return track;
		}

		mQueue[queueType].takeFirst();
	}

	emit queueChanged(queueType);

	return nullptr;
}

void MediaQueue::shuffleSystemQueue() {
	std::random_device rd;
	std::mt19937 g(rd());
	mBackupQueue = mQueue[System];
	mBackupList = mLoopingPlaylist;

	std::shuffle(mQueue[System].begin(), mQueue[System].end(), g);
	std::shuffle(mLoopingPlaylist.begin(), mLoopingPlaylist.end(), g);
	emit queueChanged(System);
}

void MediaQueue::unshuffleSystemQueue() {
	mQueue[System] = mBackupQueue;
	mLoopingPlaylist = mBackupList;
	emit queueChanged(System);
}
