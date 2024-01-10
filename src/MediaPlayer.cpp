#include "MediaPlayer.hpp"

#include "MediaQueue.hpp"

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
	if (mPlaylistId == playlistId && mTrackId == trackId) {
		return mPlayingTrack;
	}

	MediaQueue &queue = MediaQueue::instance();
	mPlaylistId = playlistId;
	mTrackId = trackId;

	queue.setPlaylist(playlistId);
	queue.skipSystemUntil(trackId);
	return mPlayingTrack = nextTrack();
}

Track *MediaPlayer::nextTrack() {
	MediaQueue &queue = MediaQueue::instance();
	Track *track = queue.next();
	setSource(QUrl::fromLocalFile("../.." + track->url()));
	return track;
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
