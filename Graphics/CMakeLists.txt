project(Graphics)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB SOURCE_FILES *cpp *qrc)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBS_QUALIFIED})
