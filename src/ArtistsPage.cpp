#include "ArtistsPage.hpp"

#include "EntityGridButton.hpp"
#include "ResourceManager.hpp"

#include <QGridLayout>

ArtistsPage::ArtistsPage(QWidget *parent) : QWidget{parent} {}

void ArtistsPage::fillList() {
	if (mFilled) {
		return;
	}

	QGridLayout *layout = new QGridLayout{scrollList()};
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 4; ++col) {
		layout->setColumnStretch(col, 1);
	}

	QList<Artist *> artists = ResourceManager::instance().getAllArtists();

	for (int i = 0; i < artists.size(); ++i) {
		auto *button = new EntityGridButton(artists[i]);
		layout->addWidget(button, i / 4, i % 4, Qt::AlignTop);
	}

	if (artists.size() > 0) {
		layout->setRowStretch(artists.size() / 4, 1);
	}

	scrollList()->setLayout(layout);
	mFilled = true;
}

const char *ArtistsPage::scrollListName() const { return "artistslist"; }

QWidget *ArtistsPage::scrollList() {
	if (!mScrollList) {
		mScrollList = findChild<QWidget *>(scrollListName());
	}

	return mScrollList;
}
