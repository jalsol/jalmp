#ifndef SEARCHPAGE_HPP
#define SEARCHPAGE_HPP

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class SearchPage : public QWidget {
	Q_OBJECT
public:
	SearchPage(QWidget *parent = nullptr);

public slots:
	// void onSearchButtonClicked();
	void onSearchTextChanged(const QString &text);
	void onSearchButtonClicked();

private:
	QLineEdit *searchInput();
	void clearList();
	QWidget *searchlist();

	// DO NOT USE THESE DIRECTLY, USE THEIR GETTERS INSTEAD
	QLineEdit *mSearchInput = nullptr;
	QWidget *mSearchList = nullptr;
};

#endif // SEARCHPAGE_HPP
