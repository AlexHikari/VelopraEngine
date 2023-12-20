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
target_link_libraries(SandboxGame PRIVATE VelopraCore VelopraRenderer VelopraWindowSystem VelopraGameLogic VelopraInputSystem VelopraFramework)

if(WIN32 AND BUILD_SHARED_LIBS)
    message(STATUS "Windows platform detected - Shared Libraries (SandboxGame)")
    add_custom_command(TARGET SandboxGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraCore>/VelopraCore.dll
        $<TARGET_FILE_DIR:SandboxGame>
        COMMENT "Copying VelopraCore DLL to executable directory (SandboxGame)"
    
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraRenderer>/VelopraRenderer.dll
        $<TARGET_FILE_DIR:SandboxGame>
        COMMENT "Copying VelopraRenderer DLL to executable directory (SandboxGame)"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraWindowSystem>/VelopraWindowSystem.dll
        $<TARGET_FILE_DIR:SandboxGame>
        COMMENT "Copying VelopraWindowSystem DLL to executable directory (SandboxGame)"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraGameLogic>/VelopraGameLogic.dll
        $<TARGET_FILE_DIR:SandboxGame>
        COMMENT "Copying VelopraGameLogic DLL to executable directory (SandboxGame)"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraInputSystem>/VelopraInputSystem.dll
        $<TARGET_FILE_DIR:SandboxGame>
        COMMENT "Copying VelopraInputSystem DLL to executable directory (SandboxGame)"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraFramework>/VelopraFramework.dll
        $<TARGET_FILE_DIR:SandboxGame>
        COMMENT "Copying VelopraFramework DLL to executable directory (SandboxGame)"
    )
elseif(APPLE AND BUILD_SHARED_LIBS)
    # macOS-specific commands
elseif(UNIX AND NOT APPLE AND BUILD_SHARED_LIBS)
    # Linux-specific commands
elseif(NOT BUILD_SHARED_LIBS)
    message(STATUS "Built as static library (SandboxGame)")
else()
    message(WARNING "Platform not recognized (SandboxGame)")
endif()

add_custom_command(TARGET SandboxGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${EXAMPLE_DIR}"
                    $<TARGET_FILE_DIR:SandboxGame>
                    COMMENT "Copying example from ${EXAMPLE_DIR} to executable directory (SandboxGame)")