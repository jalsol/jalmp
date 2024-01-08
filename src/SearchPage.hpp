#ifndef SEARCHPAGE_HPP
#define SEARCHPAGE_HPP

#include "Page.hpp"

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class SearchPage : public Page {
public:
	SearchPage(QWidget *parent = nullptr);
	void fillList() override;

public slots:
	void onSearchButtonClicked();

private:
	const char *scrollListName() const override;

	QLineEdit *searchInput();
	QLineEdit *mSearchInput = nullptr;
};

#endif // SEARCHPAGE_HPP
