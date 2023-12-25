#include "TrackListButton.hpp"

TrackListButton::TrackListButton(QWidget *parent) : QPushButton(parent) {}

TrackListButton::TrackListButton(Track *track, QWidget *parent)
	: QPushButton(parent) {
	setText(track->title());
	setFixedHeight(50);
}
