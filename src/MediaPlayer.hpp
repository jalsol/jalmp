#ifndef MEDIAPLAYER_HPP
#define MEDIAPLAYER_HPP

#include "Track.hpp"
#include "Types.hpp"

#include <QAudioOutput>
#include <QList>
#include <QMediaPlayer>

class MediaPlayer : public QMediaPlayer {
	Q_OBJECT
public:
	MediaPlayer(const MediaPlayer&) = delete;
	MediaPlayer& operator=(const MediaPlayer&) = delete;
	MediaPlayer(MediaPlayer&&) = delete;
	MediaPlayer& operator=(MediaPlayer&&) = delete;

	static MediaPlayer* instance();
	static void init(QObject* parent = nullptr);

	bool isMuted() const;
	Track* invokeTrack(PlaylistId playlistId, TrackId trackId);
	Track* nextTrack();
	Track* prevTrack();
	PlaylistId playlistId() const;

	int volume() const;
	void toggleMuteVolume();
	void cacheVolume();
	void setVolume(int volume);

signals:
	void trackLoaded(TrackId trackId);

private:
	MediaPlayer();
	~MediaPlayer();
	void loadTrack(Track* track);

	QAudioOutput* audioOutput = new QAudioOutput();
	bool mMute = false;
	int mVolume = 100;
	int mCachedVolume = -1;
	PlaylistId mPlaylistId = PlaylistId::Invalid;
	TrackId mTrackId = TrackId::Invalid;
};

#endif // MEDIAPLAYER_HPP
