#include "MediaSlider.hpp"

MediaSlider::MediaSlider(Qt::Orientation orientation, QWidget *parent)
	: QSlider(orientation, parent) {}

MediaSlider::MediaSlider(QWidget *parent) : QSlider(parent) {}

void MediaSlider::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {

		int range = maximum() - minimum();
		int clickPosition = (orientation() == Qt::Horizontal)
								? event->pos().x()
								: event->pos().y();
		int newPosition =
			minimum()
			+ (range * clickPosition)
				  / (orientation() == Qt::Horizontal ? width() : height());

		setValue(newPosition);

		QSlider::mousePressEvent(event);
	}
}
