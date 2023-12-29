cmake_minimum_required(VERSION 3.14)

project(tests LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)


set(TEST_SOURCES
        main.cpp

)

set(CPP_SOURCES
        ../src/lib/muparser/muParser.cpp
        ../src/lib/muparser/muParser.h
        ../src/lib/muparser/muParserBase.cpp
        ../src/lib/muparser/muParserBase.h
        ../src/lib/muparser/muParserBytecode.cpp
        ../src/lib/muparser/muParserBytecode.h
        ../src/lib/muparser/muParserCallback.cpp
        ../src/lib/muparser/muParserCallback.h
        ../src/lib/muparser/muParserDef.h
        ../src/lib/muparser/muParserDLL.cpp
        ../src/lib/muparser/muParserDLL.h
        ../src/lib/muparser/muParserError.cpp
        ../src/lib/muparser/muParserError.h
        ../src/lib/muparser/muParserFixes.h
        ../src/lib/muparser/muParserInt.cpp
        ../src/lib/muparser/muParserInt.h
        ../src/lib/muparser/muParserTemplateMagic.h
        ../src/lib/muparser/muParserTest.cpp
        ../src/lib/muparser/muParserTest.h
        ../src/lib/muparser/muParserToken.h
        ../src/lib/muparser/muParserTokenReader.cpp
        ../src/lib/muparser/muParserTokenReader.h

        ../src/Function.h
        ../src/Function.cpp

        ../src/Obstacle.cpp
        ../src/Obstacle.h

        ../src/Player.cpp
        ../src/Player.h
)


add_executable( tests ${TEST_SOURCES} ${CPP_SOURCES} catch.hpp
  main.cpp
  function_tests.cpp
)
target_link_libraries(tests Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)
install(TARGETS tests
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
