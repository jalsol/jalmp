#ifndef DURATIONLABEL_HPP
#define DURATIONLABEL_HPP

#include <QLabel>
#include <QTime>

class DurationLabel : public QLabel {
public:
	DurationLabel(QWidget *parent = nullptr);
	DurationLabel(QTime duration, QWidget *parent = nullptr);

	void setDuration(QTime duration);
	void setDuration(qint64 duration);
	void increment();
	void reset();

private:
	// QTime mDuration;
};

#endif // DURATIONLABEL_HPP
