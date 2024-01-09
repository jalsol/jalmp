#include "ArtistsPage.hpp"

#include "EntityGridButton.hpp"
#include "ResourceManager.hpp"

#include <QGridLayout>

ArtistsListCapture::ArtistsListCapture(QWidget *parent)
	: ScrollListCapture{parent} {}

ArtistsListCapture::ArtistsListCapture(const QString &capture, QWidget *parent)
	: ScrollListCapture(capture, parent) {}

void ArtistsListCapture::loadArtists() {
	if (!mFilled) {
		fill();
	}
}

void ArtistsListCapture::fill() {
	if (mFilled) {
		return;
	}

	QGridLayout *layout = new QGridLayout{get()};
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

	get()->setLayout(layout);
	mFilled = true;
}

ArtistsPage::ArtistsPage(QWidget *parent) : Page{parent} {}

void ArtistsPage::fill() { mList.loadArtists(); }
