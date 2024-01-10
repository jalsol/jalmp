#ifndef UPQUEUEBUTTON_H
#define UPQUEUEBUTTON_H

#include "Types.hpp"

#include <QPushButton>
#include <QString>

class UpQueueButton : public QPushButton {
public:
	UpQueueButton(QWidget *parent = nullptr);
	UpQueueButton(int queueType, TrackId trackId, QWidget *parent = nullptr);

public slots:
	void upFromQueue();

private:
	void setInternalState();

	TrackId mTrackId;
	QString mPath;
	int mQueueType;
};

#endif // UPQUEUEBUTTON_H
