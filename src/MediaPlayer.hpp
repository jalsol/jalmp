#ifndef MEDIAPLAYER_HPP
#define MEDIAPLAYER_HPP

#include <QAudioOutput>
#include <QMediaPlayer>

class MediaPlayer : public QMediaPlayer {
public:
	MediaPlayer(const MediaPlayer&) = delete;
	MediaPlayer& operator=(const MediaPlayer&) = delete;
	MediaPlayer(MediaPlayer&&) = delete;
	MediaPlayer& operator=(MediaPlayer&&) = delete;

	static MediaPlayer* instance();
	static void init(QObject* parent = nullptr);

	bool isMuted() const;

public slots:
	void setVolume(int volume);
	void toggleMuteVolume();
	void cacheVolume();

private:
	MediaPlayer();
	~MediaPlayer();

	QAudioOutput* audioOutput = new QAudioOutput();
	bool mMute = false;
	int mVolume = 100;
	int mCachedVolume = -1;
};

#endif // MEDIAPLAYER_HPP
