#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <QPushButton>
#include <QString>
#include <QWidget>

class ToggleButton : public QPushButton {
public:
	ToggleButton(QWidget* parent = nullptr);

	void setChecked(bool checked);
	void setOnTexture(const QString& textureOn);
	void setOffTexture(const QString& textureOff);

private:
	QString mTextureOn;
	QString mTextureOff;
};

#endif // TOGGLEBUTTON_H
