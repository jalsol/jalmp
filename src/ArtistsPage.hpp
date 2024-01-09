#ifndef ARTISTSPAGE_HPP
#define ARTISTSPAGE_HPP

#include "Page.hpp"
#include "ScrollListCapture.hpp"

class ArtistsListCapture : public ScrollListCapture {
public:
	ArtistsListCapture(QWidget *parent = nullptr);
	ArtistsListCapture(const QString &capture, QWidget *parent = nullptr);

	void loadArtists();

private:
	void fill() override;

	bool mFilled = false;
};

class ArtistsPage : public Page {
public:
	ArtistsPage(QWidget *parent = nullptr);
	void fill();

private:
	ArtistsListCapture mList = ArtistsListCapture("artistsList", this);

	bool mFilled = false;
};

#endif // ARTISTSPAGE_HPP
