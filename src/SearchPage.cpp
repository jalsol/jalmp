#include "SearchPage.hpp"

#include "AddQueueButton.hpp"
#include "EntityListButton.hpp"
#include "FavoriteButton.hpp"
#include "IndexLabel.hpp"
#include "MediaQueue.hpp"
#include "ResourceManager.hpp"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>

SearchListCapture::SearchListCapture(QWidget *parent)
	: ScrollListCapture{parent} {}

SearchListCapture::SearchListCapture(const QString &capture, QWidget *parent)
	: ScrollListCapture{capture, parent} {}

void SearchListCapture::loadResultFrom(const QString &keyword) {
	if (mKeyword == keyword) {
		return;
	}

	if (keyword.isEmpty()) {
		clear();
		return;
	}

	mKeyword = keyword;
	reload();
}

void SearchListCapture::fill() {
	ResourceManager &rm = ResourceManager::instance();
	auto entities = rm.getEntitiesByKeyword(mKeyword);

	auto tracks = [&entities]() {
		QList<Track *> tracks;
		for (auto *entity : entities) {
			if (entity->type() == EntityType::Track) {
				tracks.append(static_cast<Track *>(entity));
			}
		}
		return tracks;
	}();
	MediaQueue::instance().setPlaylist(PlaylistId::Search, tracks);

	QGridLayout *layout = new QGridLayout{get()};
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 4; ++col) {
		layout->setColumnStretch(col, 1);
	}

	int row = 0;
	for (auto *entity : entities) {
		int col = 0;
		{
			auto *idLabel = new IndexLabel(row + 1);
			layout->addWidget(idLabel, row, col++, Qt::AlignTop);
		}

		{
			auto *trackButton = new EntityListButton(entity);
			layout->addWidget(trackButton, row, col++, Qt::AlignTop);
		}

		if (entity->type() == EntityType::Track) {
			Track *_entity = (Track *)entity;
			{
				auto *favoriteButton = new FavoriteButton(
					(qint64)_entity->id(), _entity->isFavorite());
				layout->addWidget(favoriteButton, row, col++, Qt::AlignTop);
			}
			{
				auto *addQueueButton =
					new AddQueueButton((qint64)_entity->id());
				layout->addWidget(addQueueButton, row, col++, Qt::AlignTop);
			}
		}

		++row;
	}

	if (row > 0) {
		layout->setRowStretch(row - 1, 1);
	}

	// set the scroll area's widget
	get()->setLayout(layout);
}

SearchPage::SearchPage(QWidget *parent) : Page{parent} {}

void SearchPage::fill() {
	const auto &input = mSearchInput.get()->text();
	if (input.isEmpty()) {
		return;
	}

	mList.loadResultFrom(input);
}

void SearchPage::onSearchButtonClicked() { fill(); }
