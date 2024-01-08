#ifndef SINGLEARTISTPAGE_HPP
#define SINGLEARTISTPAGE_HPP

#include "Page.hpp"
#include "Types.hpp"

#include <QLabel>
#include <QPixmap>
#include <QWidget>

class SingleArtistPage : public Page {
public:
	SingleArtistPage(QWidget *parent = nullptr);
	void loadArtist(ArtistId artistId);

private:
	void fillList() override;
	const char *scrollListName() const override;

	QLabel *cover();
	QLabel *name();

	QPixmap mPixmap;
	ArtistId mArtistId = ArtistId::Invalid;

	QLabel *mCover = nullptr;
	QLabel *mName = nullptr;
};

#endif // SINGLEARTISTPAGE_HPP
