# Top-Level CMakeLists.txt
cmake_minimum_required (VERSION 3.8)

set(EXAMPLE_DIR "${CMAKE_SOURCE_DIR}/example")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Enable MSVC runtime library flags
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(MSVC)
    add_compile_options(/EHsc)
endif()

# For debugging included files
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /showIncludes")

project("VelopraEngine")

# Option to control building of shared or static libraries
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)" ON)

# Include subdirectories for each module
add_subdirectory("core")
add_subdirectory("input")
add_subdirectory("rendering")
add_subdirectory("window_system")
add_subdirectory("game_logic")
add_subdirectory("framework")
add_subdirectory("ui")
add_subdirectory("editor")
add_subdirectory("sandbox")