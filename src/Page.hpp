#ifndef PAGE_HPP
#define PAGE_HPP

#include <QWidget>

class Page : public QWidget {
public:
	Page(QWidget *parent = nullptr);
	// virtual void fill() = 0;
};

#endif // PAGE_HPP
