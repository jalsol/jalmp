#ifndef SINGLEARTISTPAGE_HPP
#define SINGLEARTISTPAGE_HPP

#include "Page.hpp"
#include "Types.hpp"

#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>

class SingleArtistPage : public Page {
public:
	SingleArtistPage(QWidget *parent = nullptr);
	void loadArtist(ArtistId artistId);
	ArtistId artistId() const;

private:
	void fillList() override;
	const char *scrollListName() const override;

	QLabel *cover();
	QLabel *name();
	QPushButton *albumButton();

	QPixmap mPixmap;
	ArtistId mArtistId = ArtistId::Invalid;

	QLabel *mCover = nullptr;
	QLabel *mName = nullptr;
	QPushButton *mAlbumButton = nullptr;
};

#endif // SINGLEARTISTPAGE_HPP
