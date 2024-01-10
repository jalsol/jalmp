#include "DownQueueButton.hpp"

#include "Navigator.hpp"

DownQueueButton::DownQueueButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this, &DownQueueButton::downFromQueue);
}

DownQueueButton::DownQueueButton(TrackId trackId, QWidget *parent)
	: DownQueueButton(parent) {
	mTrackId = trackId;

	// setStyleSheet(
	// 	"QPushButton { border-image: url(../../assets/1A7AD8.png); }");
	static const QIcon icon = QIcon("../../assets/4B35A8d.png");
	setIcon(icon);
	setFixedSize(35, 35);
	setInternalState();
}

void DownQueueButton::downFromQueue() {
	Navigator::instance()->navigateTo(mPath);
}

void DownQueueButton::setInternalState() {
	mPath = QString("queue_down/%1").arg(mTrackId);
}
