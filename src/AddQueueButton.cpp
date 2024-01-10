#include "AddQueueButton.hpp"

#include "Navigator.hpp"

AddQueueButton::AddQueueButton(QWidget *parent) : QPushButton(parent) {
	connect(this, &QPushButton::clicked, this, &AddQueueButton::addToQueue);
}

AddQueueButton::AddQueueButton(TrackId trackId, QWidget *parent)
	: AddQueueButton(parent) {
	mTrackId = trackId;

	// setStyleSheet(
	// 	"QPushButton { border-image: url(../../assets/1A7D10.png); }");
	static const QIcon icon = QIcon("../../assets/20C828.png");
	setIcon(icon);
	setFixedSize(35, 35);
	setInternalState();
}

void AddQueueButton::addToQueue() { Navigator::instance()->navigateTo(mPath); }

void AddQueueButton::setInternalState() {
	mPath = QString("queue_add/%1").arg(mTrackId);
}
