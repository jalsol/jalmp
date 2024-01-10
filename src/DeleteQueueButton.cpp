#include "DeleteQueueButton.hpp"

#include "Navigator.hpp"

#include <QSize>

DeleteQueueButton::DeleteQueueButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this,
			&DeleteQueueButton::deleteFromQueue);
}

DeleteQueueButton::DeleteQueueButton(TrackId trackId, QWidget *parent)
	: DeleteQueueButton(parent) {
	mTrackId = trackId;

	static const QIcon icon = QIcon("../../assets/24F050.png");
	setIcon(icon);
	setIconSize(QSize(35, 35));
	setFixedSize(35, 35);
	setInternalState();
}

void DeleteQueueButton::deleteFromQueue() {
	Navigator::instance()->navigateTo(mPath);
}

void DeleteQueueButton::setInternalState() {
	mPath = QString("queue_delete/%1").arg(mTrackId);
}
