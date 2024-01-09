#ifndef TRACKLISTPAGE_HPP
#define TRACKLISTPAGE_HPP

#include "Page.hpp"
#include "Types.hpp"

#include <QLabel>
#include <QPair>
#include <QPushButton>

class TrackListPage : public Page {
public:
	TrackListPage(QWidget *parent = nullptr);
	void loadTrackFrom(EntityId id, EntityType type);
	QPair<EntityId, EntityType> id() const;

private:
	void fillList() override;
	const char *scrollListName() const override;

	QLabel *cover();
	QLabel *name();
	QPushButton *viewOrigin();

	QPixmap mPixmap;
	EntityId mId;
	EntityType mType;

	QLabel *mCover = nullptr;
	QLabel *mName = nullptr;
	QPushButton *mViewOrigin = nullptr;
};

#endif // TRACKLISTPAGE_HPP
