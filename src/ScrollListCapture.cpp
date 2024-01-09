#include "ScrollListCapture.hpp"

#include <QLayout>

ScrollListCapture::ScrollListCapture(QWidget *parent) : WidgetCapture{parent} {}

ScrollListCapture::ScrollListCapture(const QString &capture, QWidget *parent)
	: WidgetCapture(capture, parent) {}

void ScrollListCapture::clear() {
	QLayout *layout = get()->layout();

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

void ScrollListCapture::reload() {
	clear();
	fill();
}
