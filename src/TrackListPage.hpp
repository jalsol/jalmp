#ifndef TRACKLISTPAGE_HPP
#define TRACKLISTPAGE_HPP

#include "Page.hpp"
#include "ScrollListCapture.hpp"
#include "Types.hpp"
#include "WidgetCapture.hpp"

#include <QLabel>
#include <QPair>
#include <QPushButton>

class TrackListCapture : public ScrollListCapture {
public:
	TrackListCapture(QWidget *parent = nullptr);
	TrackListCapture(const QString &capture, QWidget *parent = nullptr);

	void loadTrackFrom(EntityId id, EntityType type);
	QPair<EntityId, EntityType> id() const;

private:
	void fill() override;
	EntityId mId;
	EntityType mType;
};

class TrackListPage : public Page {
public:
	TrackListPage(QWidget *parent = nullptr);
	void fill(EntityId id, EntityType type);
	QPair<EntityId, EntityType> id() const;
	void reload();

private:
	using LabelCapture = WidgetCapture<QLabel>;
	using ButtonCapture = WidgetCapture<QPushButton>;

	TrackListCapture mList = TrackListCapture("tracklist", this);
	LabelCapture mCover = LabelCapture("tracklistCoverLabel", this);
	LabelCapture mName = LabelCapture("tracklistNameLabel", this);
	ButtonCapture mOrigin = ButtonCapture("viewTracklistOrigin", this);

	QPixmap mPixmap;
};

#endif // TRACKLISTPAGE_HPP
