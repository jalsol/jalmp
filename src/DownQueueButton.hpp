#ifndef DOWNQUEUEBUTTON_HPP
#define DOWNQUEUEBUTTON_HPP

#include "Types.hpp"

#include <QPushButton>
#include <QString>

class DownQueueButton : public QPushButton {
public:
	DownQueueButton(QWidget *parent = nullptr);
	DownQueueButton(int queueType, TrackId trackId, QWidget *parent = nullptr);

public slots:
	void downFromQueue();

private:
	void setInternalState();

	TrackId mTrackId;
	QString mPath;
	int mQueueType;
};

#endif // DOWNQUEUEBUTTON_HPP
