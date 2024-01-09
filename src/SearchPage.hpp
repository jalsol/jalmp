#ifndef SEARCHPAGE_HPP
#define SEARCHPAGE_HPP

#include "Page.hpp"
#include "ScrollListCapture.hpp"
#include "WidgetCapture.hpp"

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class SearchListCapture : public ScrollListCapture {
public:
	SearchListCapture(QWidget *parent = nullptr);
	SearchListCapture(const QString &capture, QWidget *parent = nullptr);

	void loadResultFrom(const QString &keyword);

private:
	void fill() override;

	QString mKeyword;
};

class SearchPage : public Page {
public:
	SearchPage(QWidget *parent = nullptr);
	void fill();

public slots:
	void onSearchButtonClicked();

private:
	using SearchInputCapture = WidgetCapture<QLineEdit>;

	SearchListCapture mList = SearchListCapture("searchlist", this);
	SearchInputCapture mSearchInput = SearchInputCapture("searchInput", this);
};

#endif // SEARCHPAGE_HPP
