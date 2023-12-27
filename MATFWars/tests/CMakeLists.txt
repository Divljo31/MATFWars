cmake_minimum_required(VERSION 3.14)

project(tests LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(TEST_SOURCES
        main.cpp

)

set(CPP_SOURCES
        ../lib/muparser/muParser.cpp
        ../lib/muparser/muParser.h
        ../lib/muparser/muParserBase.cpp
        ../lib/muparser/muParserBase.h
        ../lib/muparser/muParserBytecode.cpp
        ../lib/muparser/muParserBytecode.h
        ../lib/muparser/muParserCallback.cpp
        ../lib/muparser/muParserCallback.h
        ../lib/muparser/muParserDef.h
        ../lib/muparser/muParserDLL.cpp
        ../lib/muparser/muParserDLL.h
        ../lib/muparser/muParserError.cpp
        ../lib/muparser/muParserError.h
        ../lib/muparser/muParserFixes.h
        ../lib/muparser/muParserInt.cpp
        ../lib/muparser/muParserInt.h
        ../lib/muparser/muParserTemplateMagic.h
        ../lib/muparser/muParserTest.cpp
        ../lib/muparser/muParserTest.h
        ../lib/muparser/muParserToken.h
        ../lib/muparser/muParserTokenReader.cpp
        ../lib/muparser/muParserTokenReader.h

        ../Function.h
        ../Function.cpp
)


add_executable( tests ${TEST_SOURCES} ${CPP_SOURCES} catch.hpp
  main.cpp
  function_tests.cpp
)
target_link_libraries(tests Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS tests
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
