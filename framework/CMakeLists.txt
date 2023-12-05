# framework CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(VelopraFramework)

set(FRAMEWORK_SOURCE_FILES
    src/VelopraEngineApplication.cpp
)
set(FRAMEWORK_HEADER_FILES
    include/VelopraEngineApplication.h
)

# Create the Renderer library
add_library(VelopraFramework ${FRAMEWORK_SOURCE_FILES} ${FRAMEWORK_HEADER_FILES})

# Define BUILDING_RENDERER_DLL when building a shared library
if(BUILD_SHARED_LIBS)
    target_compile_definitions(VelopraFramework PRIVATE BUILDING_FRAMEWORK_DLL)
endif()


target_include_directories(VelopraFramework PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# Link with Core module and external libraries
target_link_libraries(VelopraFramework PRIVATE 
    VelopraCore
    VelopraInputSystem
    VelopraRenderer
    VelopraGameLogic
    VelopraWindowSystem
)