cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

#ovde dodati test fajlove
set(TEST_SOURCES 
    catch_main.cpp

)

set(CPP_SOURCES

)

add_executable(tests ${TEST_SOURCES} ${CPP_SOURCES} catch.hpp)




# target_link_libraries(MatfTunes PRIVATE -ltag)

