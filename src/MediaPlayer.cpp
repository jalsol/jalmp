#include "MediaPlayer.hpp"

MediaPlayer::MediaPlayer() {
	setSource(QUrl::fromLocalFile("../../assets/audio/2.mp3"));
	setAudioOutput(audioOutput);
	audioOutput->setVolume(mVolume);
}

MediaPlayer::~MediaPlayer() { delete audioOutput; }

MediaPlayer *MediaPlayer::instance() {
	static MediaPlayer *instance = new MediaPlayer();
	return instance;
}

void MediaPlayer::setVolume(int volume) {
	mVolume = volume;
	audioOutput->setVolume(volume / 100.F);

	if (volume == 0) {
		mMute = true;
	} else {
		mMute = false;
	}
}

bool MediaPlayer::isMuted() const { return mMute; }

void MediaPlayer::toggleMuteVolume() {
	if (!mMute) {
		mCachedVolume = mVolume;
		mVolume = 0;
	} else {
		mVolume = mCachedVolume;
	}

	setVolume(mVolume);
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
