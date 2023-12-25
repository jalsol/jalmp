#ifndef SINGLEARTISTPAGE_HPP
#define SINGLEARTISTPAGE_HPP

#include "Types.hpp"

#include <QLabel>
#include <QPixmap>
#include <QWidget>

class SingleArtistPage : public QWidget {
	Q_OBJECT
public:
	SingleArtistPage(QWidget *parent = nullptr);

	void loadArtist(ArtistId artistId);

private:
	void clearList();
	QWidget *tracklist();
	QLabel *cover();
	QLabel *name();

	QPixmap mPixmap;
	ArtistId mArtistId = ArtistId::Invalid;

	// DO NOT USE THESE DIRECTLY, USE THEIR GETTERS INSTEAD
	QWidget *mTracklist = nullptr;
	QLabel *mCover = nullptr;
	QLabel *mName = nullptr;
};

#endif // SINGLEARTISTPAGE_HPP
