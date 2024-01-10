#include "UpQueueButton.hpp"

#include "Navigator.hpp"

UpQueueButton::UpQueueButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this, &UpQueueButton::upFromQueue);
}

UpQueueButton::UpQueueButton(TrackId trackId, QWidget *parent)
	: UpQueueButton(parent) {
	mTrackId = trackId;

	// setStyleSheet(
	// 	"QPushButton { border-image: url(../../assets/1A7D10.png); }");
	static const QIcon icon = QIcon("../../assets/4B35A8u.png");
	setIcon(icon);
	setFixedSize(35, 35);
	setInternalState();
}

void UpQueueButton::upFromQueue() { Navigator::instance()->navigateTo(mPath); }

void UpQueueButton::setInternalState() {
	mPath = QString("queue_up/%1").arg(mTrackId);
}
