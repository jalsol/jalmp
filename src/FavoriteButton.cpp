#include "FavoriteButton.hpp"

#include "Navigator.hpp"

FavoriteButton::FavoriteButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this, &FavoriteButton::toggleFavorite);
}

FavoriteButton::FavoriteButton(TrackId trackId, bool favorite, QWidget *parent)
	: FavoriteButton(parent) {
	mTrackId = trackId;
	mFavorite = favorite;

	setFixedSize(35, 35);
	setInternalState();
}

void FavoriteButton::setTrackId(TrackId trackId) {
	mTrackId = trackId;
	setInternalState();
}

void FavoriteButton::setFavorite(bool favorite) {
	mFavorite = favorite;
	setInternalState();
}

void FavoriteButton::toggleFavorite() {
	mFavorite = !mFavorite;
	setInternalState();

	Navigator::instance()->navigateTo(mPath);
}

void FavoriteButton::setInternalState() {
	if (mFavorite) {
		static const QIcon icon = QIcon("../../assets/10D6B0.png");
		setIcon(icon);
	} else {
		static const QIcon icon = QIcon("../../assets/10CA18.png");
		setIcon(icon);
	}

	if (mFavorite) {
		mPath = QString("track/%1/like").arg(mTrackId);
		setChecked(true);
	} else {
		mPath = QString("track/%1/unlike").arg(mTrackId);
		setChecked(false);
	}
}
