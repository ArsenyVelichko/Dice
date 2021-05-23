project(UI)

set(HEADER_FILES MainWindow.h)
set(SOURCE_FILES MainWindow.cpp MainWindow.ui)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBS_QUALIFIED} Graphics)
