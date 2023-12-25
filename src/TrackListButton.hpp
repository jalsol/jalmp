#ifndef TRACKLISTBUTTON_HPP
#define TRACKLISTBUTTON_HPP

#include "Track.hpp"

#include <QPushButton>

class TrackListButton : public QPushButton {
public:
	TrackListButton(QWidget *parent = nullptr);
	TrackListButton(Track *track, QWidget *parent = nullptr);
};

#endif // TRACKLISTBUTTON_HPP
