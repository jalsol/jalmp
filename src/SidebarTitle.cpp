#include "SidebarTitle.hpp"

#include "ResourceManager.hpp"
#include "Track.hpp"

#include <QString>
#include <QtSql>

SidebarTitle::SidebarTitle(QWidget* parent) : QLabel(parent) {
	setTextInteractionFlags(Qt::TextBrowserInteraction);
}

void SidebarTitle::setTitle(TrackId trackId) {
	ResourceManager& rm = ResourceManager::instance();
	Track* track = rm.getTrack(trackId);
	Q_ASSERT(track != nullptr);

	QString song_title =
		QString("<a href=\"track/%1\"><b>%2</b></a>")
			.arg(QString::number(int64_t(trackId)), track->name());

	QList<Artist*> artists = rm.getArtistsByTrack(trackId);

	QString artist_title = "";
	for (auto* artist : artists) {
		artist_title +=
			QString("<a href=\"artist/%1\">%2</a> ")
				.arg(QString::number(int64_t(artist->id())), artist->name());
	}

	setText(song_title + "<br />" + artist_title);
}
