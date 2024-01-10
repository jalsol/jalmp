#ifndef ADDQUEUEBUTTON_HPP
#define ADDQUEUEBUTTON_HPP

#include <QPushButton>

#include "Types.hpp"

#include <QPushButton>
#include <QString>

class AddQueueButton : public QPushButton {
public:
	AddQueueButton(QWidget *parent = nullptr);
	AddQueueButton(TrackId trackId, QWidget *parent = nullptr);

public slots:
	void addToQueue();

private:
	void setInternalState();

	TrackId mTrackId;
	QString mPath;
};

#endif // ADDQUEUEBUTTON_HPP
