#include "SearchPage.hpp"

#include "EntityListButton.hpp"
#include "ResourceManager.hpp"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>

SearchPage::SearchPage(QWidget *parent) : QWidget{parent} {}

QLineEdit *SearchPage::searchInput() {
	if (!mSearchInput) {
		mSearchInput = findChild<QLineEdit *>("searchInput");
	}
	return mSearchInput;
}

void SearchPage::onSearchTextChanged(const QString &text) { qDebug() << text; }

void SearchPage::onSearchButtonClicked() {
	clearList();

	const auto &input = searchInput()->text();
	if (input.isEmpty()) {
		return;
	}

	ResourceManager &rm = ResourceManager::instance();
	auto entities = rm.getEntitiesByKeyword(input);

	QGridLayout *layout = new QGridLayout{searchlist()};
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int col = 0; col < 2; ++col) {
		layout->setColumnStretch(col, 1);
	}

	int row = 0;
	for (auto *entity : entities) {
		auto *idLabel = new QLabel();
		idLabel->setText(QString::number(row + 1));
		idLabel->setFixedSize(50, 50);
		idLabel->setAlignment(Qt::AlignCenter);
		layout->addWidget(idLabel, row, 0, Qt::AlignTop);

		auto *trackButton = new EntityListButton(entity);
		layout->addWidget(trackButton, row, 1, Qt::AlignTop);

		++row;
	}

	if (row > 0) {
		layout->setRowStretch(row - 1, 1);
	}

	// set the scroll area's widget
	searchlist()->setLayout(layout);
}

void SearchPage::clearList() {
	QLayout *layout = searchlist()->layout();

	if (layout == nullptr) {
		return;
	}

	QLayoutItem *item;
	while ((item = layout->takeAt(0)) != nullptr) {
		delete item->widget();
		delete item;
	}

	delete layout;
}

QWidget *SearchPage::searchlist() {
	if (mSearchList == nullptr) {
		mSearchList = findChild<QWidget *>("searchlist");
	}

	return mSearchList;
}
