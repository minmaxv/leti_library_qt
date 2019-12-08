cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(leti_library_qt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DCMAKE_SH="CMAKE_SH-NOTFOUND")

find_package(Qt5 COMPONENTS Widgets Core Quick Sql REQUIRED)


set(llibqt_sources
        src/mainwindow.cpp
        src/database.cpp
        )

set(llibqt_headers
        src/mainwindow.h
        src/database.h
        )

set(llibqt_ui
        ui/mainwindow.ui
        )

add_executable(leti_library_qt
        main.cpp
        ${llibqt_sources}
        ${llibqt_headers}
        ${llibqt_ui}
        )


target_include_directories(leti_library_qt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(leti_library_qt PRIVATE Qt5::Widgets Qt5::Core Qt5::Quick Qt5::Sql)
