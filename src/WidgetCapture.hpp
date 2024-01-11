#ifndef WIDGETCAPTURE_HPP
#define WIDGETCAPTURE_HPP

#include <QWidget>

template <class WidgetClass> class WidgetCapture : public QWidget {
public:
	WidgetCapture(QWidget *parent = nullptr);
	WidgetCapture(const QString &capture, QWidget *parent = nullptr);

	WidgetClass *get();

protected:
	QString mCapture;
	WidgetClass *mWidget = nullptr;
};

template <class WidgetClass>
WidgetCapture<WidgetClass>::WidgetCapture(QWidget *parent) : QWidget{parent} {}

template <class WidgetClass>
WidgetCapture<WidgetClass>::WidgetCapture(const QString &capture,
										  QWidget *parent)
	: QWidget{parent}, mCapture{capture} {
}

template <class WidgetClass> WidgetClass *WidgetCapture<WidgetClass>::get() {
	if (!mWidget) {
		mWidget = parent()->template findChild<WidgetClass *>(mCapture);
	}

	Q_ASSERT(mWidget != nullptr);

	return mWidget;
}

#endif // WIDGETCAPTURE_HPP
