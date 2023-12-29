cmake_minimum_required(VERSION 3.5)

project(MATFWars VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)


set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MATFWars
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/Player.h src/Player.cpp
        src/Function.h src/Function.cpp
        src/Obstacle.h src/Obstacle.cpp
        src/lib/muparser/muParser.cpp src/lib/muparser/muParser.h
        src/lib/muparser/muParserBase.cpp src/lib/muparser/muParserBase.h
        src/lib/muparser/muParserBytecode.cpp src/lib/muparser/muParserBytecode.h
        src/lib/muparser/muParserCallback.cpp src/lib/muparser/muParserCallback.h
        src/lib/muparser/muParserDef.h src/lib/muparser/muParserDLL.cpp
        src/lib/muparser/muParserDLL.h src/lib/muparser/muParserError.cpp
        src/lib/muparser/muParserError.h src/lib/muparser/muParserFixes.h
        src/lib/muparser/muParserInt.cpp src/lib/muparser/muParserInt.h
        src/lib/muparser/muParserTemplateMagic.h src/lib/muparser/muParserTest.cpp
        src/lib/muparser/muParserTest.h src/lib/muparser/muParserToken.h
        src/lib/muparser/muParserTokenReader.cpp src/lib/muparser/muParserTokenReader.h
        src/guessgame.h src/guessgame.cpp src/guessgame.ui
        src/wargame.h src/wargame.cpp src/wargame.ui
        src/create.h src/create.cpp src/create.ui
        src/join.h src/join.cpp src/join.ui
        src/winner.h src/winner.cpp src/winner.ui
        src/check.h src/check.cpp src/check.ui
        src/warchoose.h src/warchoose.cpp src/warchoose.ui
        src/FunctionNode.h src/FunctionNode.cpp
        src/Canvas.h src/Canvas.cpp
        src/settings.h src/settings.cpp src/settings.ui
        src/leaderboard.h src/leaderboard.cpp src/leaderboard.ui

        src/Timer.h src/Timer.cpp
        src/Difficulty.h
        src/Client.h src/Client.cpp
        src/PlayerNode.h src/PlayerNode.cpp
        src/Client.h src/Client.cpp
        src/choosedifficulty.h src/choosedifficulty.cpp src/choosedifficulty.ui
        src/result.h src/result.cpp src/result.ui

        src/ObstacleNode.h src/ObstacleNode.cpp
        src/help.h src/help.cpp src/help.ui

        resources/resources.qrc
        resources/txt/leaderboard.txt
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MATFWars APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MATFWars SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MATFWars
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MATFWars PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt6::Network)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MATFWars)
endif()
set_target_properties(MATFWars PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MATFWars
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MATFWars)
endif()
