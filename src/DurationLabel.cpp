#include "DurationLabel.hpp"

DurationLabel::DurationLabel(QWidget *parent) : QLabel(parent) {
	setDuration(0);
}

DurationLabel::DurationLabel(QTime duration, QWidget *parent)
	: DurationLabel(parent) {
	setDuration(duration);
	setFixedSize(40, 35);
	setAlignment(Qt::AlignCenter);
	setStyleSheet("background: #d6d2ce;");
}

void DurationLabel::setDuration(QTime duration) {
	// mDuration = duration;
	setText(duration.toString("mm:ss"));
}

void DurationLabel::setDuration(qint64 duration) {
	setDuration(QTime(0, 0, 0, 0).addMSecs(duration));
}
