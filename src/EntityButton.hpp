#ifndef ENTITYBUTTON_HPP
#define ENTITYBUTTON_HPP

#include "Entity.hpp"

#include <QPushButton>

class EntityButton : public QPushButton {
public:
	EntityButton(QWidget *parent = nullptr);
	EntityButton(Entity *entity, PlaylistId playlistId = PlaylistId::Invalid,
				 QWidget *parent = nullptr);

public slots:
	virtual void onClicked();

protected:
	QString mPath;
	PlaylistId mPlaylistId;
};

#endif // ENTITYBUTTON_HPP
