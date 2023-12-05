# sandbox CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(SandboxGame)

set(SANDBOX_SOURCE_FILES
    src/SandboxApp.cpp
    src/SandboxMain.cpp
)
set(SANDBOX_HEADER_FILES
    include/SandboxApp.h
)

# Define the sandbox executable
add_executable(SandboxGame src/SandboxMain.cpp src/SandboxApp.cpp)

# Specify include directories
target_include_directories(SandboxGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# Link with the engine's modules
target_link_libraries(SandboxGame PRIVATE VelopraCore VelopraRenderer VelopraWindowSystem VelopraFramework VelopraGameLogic)
