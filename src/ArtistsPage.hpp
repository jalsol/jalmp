#ifndef ARTISTSPAGE_HPP
#define ARTISTSPAGE_HPP

#include "Page.hpp"

class ArtistsPage : public Page {
public:
	ArtistsPage(QWidget *parent = nullptr);
	void fillList() override;

private:
	const char *scrollListName() const override;

	bool mFilled = false;
};

#endif // ARTISTSPAGE_HPP
