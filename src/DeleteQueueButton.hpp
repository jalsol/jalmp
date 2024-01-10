#ifndef DELETEQUEUEBUTTON_H
#define DELETEQUEUEBUTTON_H

#include "Types.hpp"

#include <QPushButton>
#include <QString>

class DeleteQueueButton : public QPushButton {
public:
	DeleteQueueButton(QWidget *parent = nullptr);
	DeleteQueueButton(int queueType, TrackId trackId,
					  QWidget *parent = nullptr);

public slots:
	void deleteFromQueue();

private:
	void setInternalState();

	TrackId mTrackId;
	QString mPath;
	int mQueueType;
};

#endif // DELETEQUEUEBUTTON_H
