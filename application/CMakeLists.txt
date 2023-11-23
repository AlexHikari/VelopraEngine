# application/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

# Define the application executable
add_executable(VelopraEngine src/main.cpp)

# Link with the core, rendering, and input modules
target_link_libraries(VelopraEngine PRIVATE VelopraCore VelopraRenderer VelopraUI VelopraInputSystem)

if(WIN32)
    foreach(MODULE_NAME IN LISTS MODULE_NAMES)
        foreach(CONFIG IN ITEMS Debug Release)
            # Convert the configuration name to lowercase
            string(TOLOWER "${CONFIG}" CONFIG_LOWER)

            # Construct the DLL path
            set(DLL_PATH "${CMAKE_SOURCE_DIR}/out/build/${CMAKE_VS_PLATFORM_NAME}-${CONFIG_LOWER}/${MODULE_NAME}/${CONFIG}")

            # Check if the DLL path exists
            if(EXISTS "${DLL_PATH}")
                # Add custom command to copy DLLs
                add_custom_command(TARGET VelopraEngine POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${DLL_PATH}"
                    $<TARGET_FILE_DIR:VelopraEngine>
                    COMMENT "Copying DLLs from ${DLL_PATH} to executable $<TARGET_FILE_DIR:VelopraEngine> directory")
            endif()
        endforeach()
    endforeach()
elseif(APPLE)
    # macOS-specific commands
    # Use install_name_tool or similar
elseif(UNIX AND NOT APPLE)
    # Linux-specific commands
    # Install to /usr/local/lib or similar
endif()

add_custom_command(TARGET VelopraEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${EXAMPLE_DIR}"
                    $<TARGET_FILE_DIR:VelopraEngine>
                    COMMENT "Copying example from ${EXAMPLE_DIR}")