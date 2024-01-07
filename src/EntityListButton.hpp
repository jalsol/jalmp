#ifndef ENTITYLISTBUTTON_HPP
#define ENTITYLISTBUTTON_HPP

#include "Entity.hpp"

#include <QPushButton>
#include <QString>

class EntityListButton : public QPushButton {
public:
	EntityListButton(QWidget *parent = nullptr);
	EntityListButton(Entity *entity,
					 PlaylistId playlistId = PlaylistId::Invalid,
					 QWidget *parent = nullptr);

public slots:
	void onClicked();

private:
	QString mPath;
	PlaylistId mPlaylistId;
};

#endif // ENTITYLISTBUTTON_HPP
