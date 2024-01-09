#ifndef DURATIONLABEL_HPP
#define DURATIONLABEL_HPP

#include <QLabel>
#include <QTime>

class DurationLabel : public QLabel {
public:
	DurationLabel(QTime duration);
};

#endif // DURATIONLABEL_HPP
