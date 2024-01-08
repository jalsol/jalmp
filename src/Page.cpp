#include "Page.hpp"

#include <QLayout>

Page::Page(QWidget *parent) : QWidget{parent} {}

QWidget *Page::scrollList() {
	if (!mScrollList) {
		mScrollList = findChild<QWidget *>(scrollListName());
	}

	return mScrollList;
}

void Page::clearList() {
	QLayout *layout = scrollList()->layout();

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
