#include "FavoriteButton.hpp"

#include "Navigator.hpp"

FavoriteButton::FavoriteButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this, &FavoriteButton::toggleFavorite);
	setCheckable(true);
}

FavoriteButton::FavoriteButton(TrackId trackId, bool favorite, QWidget *parent)
	: FavoriteButton(parent) {
	mTrackId = trackId;
	mFavorite = favorite;

	setText("Like");
	setFixedSize(50, 50);
	setInternalState();
}

void FavoriteButton::toggleFavorite() {
	mFavorite = !mFavorite;
	setInternalState();

	Navigator::instance()->navigateTo(mPath);
}

void FavoriteButton::setInternalState() {
	if (mFavorite) {
		mPath = QString("track/%1/like").arg(mTrackId);
		setChecked(true);
	} else {
		mPath = QString("track/%1/unlike").arg(mTrackId);
		setChecked(false);
	}
}
