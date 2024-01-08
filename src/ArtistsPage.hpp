#ifndef ARTISTSPAGE_HPP
#define ARTISTSPAGE_HPP

#include <QWidget>

class ArtistsPage : public QWidget {
	Q_OBJECT
public:
	ArtistsPage(QWidget *parent = nullptr);

public:
	void fillList();

private:
	const char *scrollListName() const;
	QWidget *scrollList();

	QWidget *mScrollList = nullptr;
	bool mFilled = false;
};

#endif // ARTISTSPAGE_HPP
