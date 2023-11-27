# application/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# Define the application executable
add_executable(VelopraEngine src/main.cpp)

# Link with the core, rendering, and input modules
target_link_libraries(VelopraEngine PRIVATE VelopraCore VelopraRenderer VelopraUI VelopraInputSystem)

if(WIN32)
    message(STATUS "Windows platform detected")
    add_custom_command(TARGET VelopraEngine POST_BUILD
        
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraCore>/VelopraCore.dll
        $<TARGET_FILE_DIR:VelopraEngine>
        COMMENT "Copying VelopraCore DLL to executable directory"
    
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraRenderer>/VelopraRenderer.dll
        $<TARGET_FILE_DIR:VelopraEngine>
        COMMENT "Copying VelopraRenderer DLL to executable directory"
    
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraUI>/VelopraUI.dll
        $<TARGET_FILE_DIR:VelopraEngine>
        COMMENT "Copying VelopraUI DLL to executable directory"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:VelopraInputSystem>/VelopraInputSystem.dll
        $<TARGET_FILE_DIR:VelopraEngine>
        COMMENT "Copying VelopraInputSystem DLL to executable directory"
    )
elseif(APPLE)
    message(STATUS "Apple platform detected")
    # macOS-specific commands
    # Use install_name_tool or similar
elseif(UNIX AND NOT APPLE)
    message(STATUS "Unix platform detected")
    # Linux-specific commands
    # Install to /usr/local/lib or similar
else()
    message(WARNING "Platform not recognized")
endif()


add_custom_command(TARGET VelopraEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${EXAMPLE_DIR}"
                    $<TARGET_FILE_DIR:VelopraEngine>
                    COMMENT "Copying example from ${EXAMPLE_DIR}")