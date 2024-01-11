#include "MediaPlayer.hpp"

#include "MediaQueue.hpp"
#include "ResourceManager.hpp"
#include "SocketClient.hpp"

MediaPlayer::MediaPlayer() {
	setAudioOutput(audioOutput);
	audioOutput->setVolume(mVolume);
}

MediaPlayer::~MediaPlayer() { delete audioOutput; }

MediaPlayer *MediaPlayer::instance() {
	static MediaPlayer *instance = new MediaPlayer();
	return instance;
}

void MediaPlayer::setVolume(int volume) {
	if (volume == 0) {
		mMute = true;
	} else {
		mMute = false;
	}

	mVolume = volume;
	audioOutput->setVolume(volume / 100.F);
}

int MediaPlayer::volume() const { return mVolume; }

bool MediaPlayer::isMuted() const { return mMute; }

Track *MediaPlayer::invokeTrack(PlaylistId playlistId, TrackId trackId) {
	MediaQueue &queue = MediaQueue::instance();
	ResourceManager &rm = ResourceManager::instance();

	bool fromUserQueue = playlistId == PlaylistId::UserQueue;
	bool fromFavoriteQueue = playlistId == PlaylistId::Favorites;

	if (!fromUserQueue) {
		if (fromFavoriteQueue) {
			queue.setPlaylist(playlistId, rm.getAllFavoriteTracks());
		} else {
			queue.setPlaylist(playlistId);
		}
	}

	mPlaylistId = playlistId;

	if (fromUserQueue) {
		queue.skipPast(QueueType::User, trackId);
		qDebug() << "User queue skip past" << trackId;
	} else {
		queue.skipPast(QueueType::System, trackId);
		queue.refillSystemQueue();
	}

	Track *track = rm.getTrack(trackId);
	loadTrack(track);
	return track;
}

Track *MediaPlayer::nextTrack() {
	MediaQueue &queue = MediaQueue::instance();
	Track *track = queue.next();
	if (track == nullptr) {
		return nullptr;
	}

	loadTrack(track);
	return track;
}

Track *MediaPlayer::prevTrack() {
	MediaQueue &queue = MediaQueue::instance();
	Track *track = queue.prev();
	if (track == nullptr) {
		return nullptr;
	}

	loadTrack(track);
	return track;
}

void MediaPlayer::loadTrack(Track *track) {
	const auto &source =
		SocketClient::instance().sendRequest(RequestType::Audio, track->url());

	if (source.has_value()) {
		setSource(QUrl::fromLocalFile("")); // force unload
		setSource(QUrl::fromLocalFile(*source));
	} else {
		qDebug() << "MediaPlayer::loadTrack: source is empty";
	}
}

PlaylistId MediaPlayer::playlistId() const { return mPlaylistId; }

void MediaPlayer::toggleMuteVolume() {
	mMute = !mMute;

	if (mMute) {
		cacheVolume();
		setVolume(0);
	} else {
		setVolume(mCachedVolume);
	}
}

void MediaPlayer::cacheVolume() {
	if (mVolume > 0) {
		mCachedVolume = mVolume;
	}
}

void MediaPlayer::init(QObject *parent) {
	auto player = MediaPlayer::instance();
	player->setParent(parent);
}
