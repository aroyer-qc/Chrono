cmake_minimum_required(VERSION 3.16)
project(Chronometer LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
#find_package(Qt6)

qt_add_executable(Chronometer
    main.cpp
    mainwindow.h
    mainwindow.cpp
    counter.cpp
    counter.h
)

set_target_properties(Chronometer PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(Chronometer PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)
