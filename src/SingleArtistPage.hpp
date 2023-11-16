#ifndef SINGLEARTISTPAGE_HPP
#define SINGLEARTISTPAGE_HPP

#include "Types.hpp"

#include <QPixmap>
#include <QWidget>

class SingleArtistPage : public QWidget {
	Q_OBJECT
public:
	SingleArtistPage(QWidget *parent = nullptr);

	void loadArtist(ArtistId artistId);

private:
	QPixmap mPixmap;
};

#endif // SINGLEARTISTPAGE_HPP
