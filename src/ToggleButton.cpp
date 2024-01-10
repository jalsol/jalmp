#include "ToggleButton.hpp"

ToggleButton::ToggleButton(QWidget* parent) : QPushButton(parent) {
	setCheckable(true);
	setChecked(false);
}

void ToggleButton::setOnTexture(const QString& textureOn) {
	mTextureOn =
		QString("QPushButton { border-image: url(../../assets/%1.png); }")
			.arg(textureOn);
}

void ToggleButton::setOffTexture(const QString& textureOff) {
	mTextureOff =
		QString("QPushButton { border-image: url(../../assets/%1.png); }")
			.arg(textureOff);
}

void ToggleButton::setChecked(bool checked) {
	QPushButton::setChecked(checked);

	if (checked) {
		setStyleSheet(mTextureOn);
	} else {
		setStyleSheet(mTextureOff);
	}
}
