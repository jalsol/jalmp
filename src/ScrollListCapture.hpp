#ifndef SCROLLLISTCAPTURE_HPP
#define SCROLLLISTCAPTURE_HPP

#include "WidgetCapture.hpp"

#include <QString>
#include <QWidget>

class ScrollListCapture : public WidgetCapture<QWidget> {
public:
	ScrollListCapture(QWidget *parent = nullptr);
	ScrollListCapture(const QString &capture, QWidget *parent = nullptr);

	virtual void fill() = 0;
	virtual void clear();
	virtual void reload();
};

#endif // SCROLLLISTCAPTURE_HPP
