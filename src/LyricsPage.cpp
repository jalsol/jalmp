#include "LyricsPage.hpp"

#include "MediaPlayer.hpp"
#include "SocketClient.hpp"

#include <QFile>

LyricsTextCapture::LyricsTextCapture(QWidget *parent) : WidgetCapture(parent) {}

LyricsTextCapture::LyricsTextCapture(const QString &capture, QWidget *parent)
	: WidgetCapture(capture, parent) {}

void LyricsTextCapture::setLyrics(TrackId trackId) {
	auto &client = SocketClient::instance();
	const auto &lyricsOpt = client.sendRequest(
		RequestType::Lyrics, QString("/assets/lyrics/%1.txt").arg(trackId));

	if (lyricsOpt) {
		loadLyricsFromFile(*lyricsOpt);
	} else {
		get()->setText("");
	}
}

void LyricsTextCapture::loadLyricsFromFile(const QString &fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "failed to open file:" << fileName;
		get()->setText("");
		return;
	}

	QTextStream in(&file);
	get()->setText(in.readAll());
}

LyricsPage::LyricsPage(QWidget *parent) : Page(parent) {
	connect(MediaPlayer::instance(), &MediaPlayer::trackLoaded, this,
			&LyricsPage::loadTrack);
}

void LyricsPage::loadTrack(TrackId trackId) { mLyrics.setLyrics(trackId); }
