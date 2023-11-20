# input/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(VelopraUI)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Enable automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(UI_SOURCE_FILES   
    src/MainWindow.cpp
    src/QtOpenGLWidget.cpp
    src/UIManager.cpp
    src/WindowManager.cpp
)

set(UI_HEADER_FILES
    include/MainWindow.h
    include/QtOpenGLWidget.h
    include/UIManager.h
    include/WindowManager.h
)


# Create the UI library
add_library(VelopraUI ${UI_SOURCE_FILES} ${UI_HEADER_FILES})

# Include directories for Qt
target_include_directories(VelopraUI PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Qt5Widgets_INCLUDE_DIRS} 
)

# Link with Core module and Qt5Widgets
target_link_libraries(VelopraUI PRIVATE VelopraCore VelopraRenderer Qt5::Widgets)
