#ifndef FAVORITEBUTTON_HPP
#define FAVORITEBUTTON_HPP

#include "Types.hpp"

#include <QPushButton>
#include <QString>

class FavoriteButton : public QPushButton {
public:
	FavoriteButton(QWidget *parent = nullptr);
	FavoriteButton(TrackId trackId, bool favorite = false,
				   QWidget *parent = nullptr);

	void setTrackId(TrackId trackId);
	void setFavorite(bool favorite);

public slots:
	void toggleFavorite();

private:
	void setInternalState();

	TrackId mTrackId;
	bool mFavorite = false;
	QString mPath;
};

#endif // FAVORITEBUTTON_HPP
