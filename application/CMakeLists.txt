# application/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# Define the application executable
add_executable(VelopraEngine src/main.cpp)

# Link with the rendering and core modules
target_link_libraries(VelopraEngine PRIVATE VelopraCore VelopraRenderer)

# Include directories
target_include_directories(VelopraEngine PRIVATE
    ${PROJECT_SOURCE_DIR}/rendering/include
    ${PROJECT_SOURCE_DIR}/core/include
)