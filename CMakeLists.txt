cmake_minimum_required(VERSION 3.5)

project(jalmp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Multimedia)

set(PROJECT_SOURCES
        src/main.cpp
        src/MainWindow.cpp
        src/MainWindow.hpp
        src/MainWindow.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(jalmp
		MANUAL_FINALIZATION
		${PROJECT_SOURCES}
		src/Track.hpp src/Track.cpp
		src/Artist.hpp src/Artist.cpp
		src/TrackBuilder.hpp src/TrackBuilder.cpp
		src/Types.hpp
		src/Playlist.hpp src/Playlist.cpp
		src/ResourceManager.hpp src/ResourceManager.cpp
		src/ArtistBuilder.hpp src/ArtistBuilder.cpp
		src/PlaylistBuilder.hpp src/PlaylistBuilder.cpp
		src/MediaSlider.hpp src/MediaSlider.cpp
		src/SidebarTitle.hpp src/SidebarTitle.cpp
		src/SingleArtistPage.hpp src/SingleArtistPage.cpp
		src/EntityListButton.hpp src/EntityListButton.cpp
		src/MediaPlayer.hpp src/MediaPlayer.cpp
		src/SearchPage.hpp src/SearchPage.cpp
		src/Entity.hpp src/Entity.cpp
		src/Types.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET jalmp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(jalmp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(jalmp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(jalmp PRIVATE
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Sql
	Qt${QT_VERSION_MAJOR}::Multimedia
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.jalmp)
endif()
set_target_properties(jalmp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS jalmp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(jalmp)
endif()
