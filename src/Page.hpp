#ifndef PAGE_HPP
#define PAGE_HPP

#include <QWidget>

class Page : public QWidget {
public:
	Page(QWidget *parent = nullptr);
	virtual void fillList() = 0;
	virtual void clearList();

protected:
	virtual const char *scrollListName() const = 0;
	virtual QWidget *scrollList();

	QWidget *mScrollList = nullptr;
};

#endif // PAGE_HPP
