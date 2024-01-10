#include "MediaSlider.hpp"

#include <QStyle>

MediaSlider::MediaSlider(Qt::Orientation orientation, QWidget *parent)
	: QSlider(orientation, parent) {}

MediaSlider::MediaSlider(QWidget *parent) : QSlider(parent) {}

void MediaSlider::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {		
		int newPosition = QStyle::sliderValueFromPosition(
			minimum(), maximum(), event->pos().x(), width());
		setValue(newPosition);
		QSlider::mousePressEvent(event);
	}
}
