# window/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(VelopraWindowSystem)

find_package(glfw3 3.3 REQUIRED)

set(WINDOW_SYSTEM_SOURCE_FILES   
    src/VE_GLFWWindow.cpp
)

set(WINDOW_SYSTEM_HEADER_FILES
    include/VE_GLFWWindow.h
    include/VE_IWindow.h
    include/VE_WindowAPI.h
)

add_library(VelopraWindowSystem ${WINDOW_SYSTEM_SOURCE_FILES} ${WINDOW_SYSTEM_HEADER_FILES})

if(BUILD_SHARED_LIBS)
    target_compile_definitions(VelopraWindowSystem PRIVATE BUILDING_WINDOWSYSTEM_DLL)
endif()

target_include_directories(VelopraWindowSystem PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(VelopraWindowSystem PRIVATE VelopraCore VelopraRenderer VelopraInputSystem glfw)