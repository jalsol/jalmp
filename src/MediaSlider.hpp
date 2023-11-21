#ifndef MEDIASLIDER_HPP
#define MEDIASLIDER_HPP

#include <QMouseEvent>
#include <QSlider>

class MediaSlider : public QSlider
{
	Q_OBJECT
public:
	MediaSlider(Qt::Orientation, QWidget *parent = nullptr);
	MediaSlider(QWidget *parent = nullptr);

	// signals:
	//	void clicked(bool checked = false);

protected:
	void mousePressEvent(QMouseEvent *event) override;
};

#endif // MEDIASLIDER_HPP
