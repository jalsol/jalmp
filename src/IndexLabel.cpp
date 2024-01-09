#include "IndexLabel.hpp"

#include <QString>

IndexLabel::IndexLabel(int index) {
	setText(QString::number(index));
	setFixedSize(30, 35);
	setAlignment(Qt::AlignCenter);
	setStyleSheet("background: #ded9d5;");
}
