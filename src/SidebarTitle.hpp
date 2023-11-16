#ifndef SIDEBARTITLE_HPP
#define SIDEBARTITLE_HPP

#include "Track.hpp"

#include <QLabel>

class SidebarTitle : public QLabel {
public:
	explicit SidebarTitle(QWidget *parent = nullptr);

	void setTitle(TrackId trackId);
};

#endif // SIDEBARTITLE_HPP
