#ifndef DELETEQUEUEBUTTON_H
#define DELETEQUEUEBUTTON_H

#include "Types.hpp"

#include <QPushButton>
#include <QString>

class DeleteQueueButton : public QPushButton {
public:
	DeleteQueueButton(QWidget *parent = nullptr);
	DeleteQueueButton(TrackId trackId, QWidget *parent = nullptr);

public slots:
	void deleteFromQueue();

private:
	void setInternalState();

	TrackId mTrackId;
	QString mPath;
};

#endif // DELETEQUEUEBUTTON_H
