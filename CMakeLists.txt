cmake_minimum_required(VERSION 3.19)
project(ForTheRest)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(QT_LIBS Core Gui Widgets)
set(QT_LIBS_QUALIFIED Qt5::Widgets)

set(RESOURCE_FILES)

include_directories(UI Graphics)

find_package(Qt${QT_VERSION} COMPONENTS ${QT_LIBS} REQUIRED)

add_subdirectory(UI)
add_subdirectory(Graphics)

add_executable(${PROJECT_NAME} main.cpp Textures.qrc)
target_link_libraries(${PROJECT_NAME} ${QT_LIBS_QUALIFIED} UI)
