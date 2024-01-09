#include "DurationLabel.hpp"

DurationLabel::DurationLabel(QTime duration) {
	setText(duration.toString("mm:ss"));
	setFixedSize(40, 35);
	setAlignment(Qt::AlignCenter);
	setStyleSheet("background: #d6d2ce;");
}
