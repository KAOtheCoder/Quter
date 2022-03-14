cmake_minimum_required(VERSION 3.14)

project(Quter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_library(Quter SHARED
    include/Quter.h
    include/CheckableMenuButton.h
    src/CheckableMenuButton.cpp
)

target_include_directories(Quter PUBLIC ./include)

target_link_libraries(Quter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(Quter PUBLIC QUTER_LIBRARY)
