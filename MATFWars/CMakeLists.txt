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
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MATFWars
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Player.h Player.cpp
        Function.h Function.cpp
        PlayerWar.h PlayerWar.cpp

        Obstacle.h Obstacle.cpp
        lib/muparser/muParser.cpp lib/muparser/muParser.h
        lib/muparser/muParserBase.cpp lib/muparser/muParserBase.h
        lib/muparser/muParserBytecode.cpp lib/muparser/muParserBytecode.h
        lib/muparser/muParserCallback.cpp lib/muparser/muParserCallback.h
        lib/muparser/muParserDef.h lib/muparser/muParserDLL.cpp
        lib/muparser/muParserDLL.h lib/muparser/muParserError.cpp
        lib/muparser/muParserError.h lib/muparser/muParserFixes.h
        lib/muparser/muParserInt.cpp lib/muparser/muParserInt.h
        lib/muparser/muParserTemplateMagic.h lib/muparser/muParserTest.cpp
        lib/muparser/muParserTest.h lib/muparser/muParserToken.h
        lib/muparser/muParserTokenReader.cpp lib/muparser/muParserTokenReader.h

        guessgame.h guessgame.cpp guessgame.ui
        wargame.h wargame.cpp wargame.ui
        create.h create.cpp create.ui
        join.h join.cpp join.ui
        waitingroom.h waitingroom.cpp waitingroom.ui
        winner.h winner.cpp winner.ui
        check.h check.cpp check.ui
        warchoose.h warchoose.cpp warchoose.ui
        FunctionNode.h FunctionNode.cpp
        Canvas.h Canvas.cpp

        settings.h settings.cpp settings.ui
        leaderboard.h leaderboard.cpp leaderboard.ui
        resources.qrc
        Timer.h Timer.cpp

        Difficulty.h

        Confetti.h Confetti.cpp


        Client.h Client.cpp
        choosedifficulty.h choosedifficulty.cpp choosedifficulty.ui
        result.h result.cpp result.ui
        txt/leaderboard.txt





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
