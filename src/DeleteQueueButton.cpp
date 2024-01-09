#include "DeleteQueueButton.hpp"

#include "Navigator.hpp"

DeleteQueueButton::DeleteQueueButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this,
			&DeleteQueueButton::deleteFromQueue);
}

DeleteQueueButton::DeleteQueueButton(TrackId trackId, QWidget *parent)
	: DeleteQueueButton(parent) {
	mTrackId = trackId;

	static const QIcon icon = QIcon("../../assets/14F7C8.png");
	setIcon(icon);
	setFixedSize(35, 35);
	setInternalState();
}

void DeleteQueueButton::deleteFromQueue() {
	Navigator::instance()->navigateTo(mPath);
}

void DeleteQueueButton::setInternalState() {
	mPath = QString("queue_delete/%1").arg(mTrackId);
}
