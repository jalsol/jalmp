#include "MainWindow.hpp"

// #include "ResourceManager.hpp"
// #include "Track.hpp"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	//	ResourceManager& resourceManager = ResourceManager::instance();
	//	Track* track = resourceManager.getTrack(TrackId{1});

	//	if (track != nullptr)
	//		qDebug() << track->title();

	return a.exec();
}
