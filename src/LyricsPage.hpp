#ifndef LYRICSPAGE_HPP
#define LYRICSPAGE_HPP

#include "Page.hpp"
#include "Types.hpp"
#include "WidgetCapture.hpp"

#include <QTextEdit>

class LyricsTextCapture : public WidgetCapture<QTextEdit> {
public:
	LyricsTextCapture(QWidget *parent = nullptr);
	LyricsTextCapture(const QString &capture, QWidget *parent = nullptr);

	void setLyrics(TrackId trackId);

private:
	void loadLyricsFromFile(const QString &fileName);
};

class LyricsPage : public Page {
public:
	LyricsPage(QWidget *parent = nullptr);

public slots:
	void loadTrack(TrackId trackId);

private:
	LyricsTextCapture mLyrics = LyricsTextCapture("lyricsText", this);
};

#endif // LYRICSPAGE_HPP
