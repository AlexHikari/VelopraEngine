# application/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# Define the application executable
add_executable(VelopraEngine src/main.cpp)

# Link with the core, rendering, and input modules
target_link_libraries(VelopraEngine PRIVATE VelopraCore VelopraRenderer VelopraInputSystem)
