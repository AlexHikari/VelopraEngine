# game_logic/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(VelopraGameLogic)

set(GAME_LOGIC_SOURCE_FILES   
    src/VE_GameObject2D.cpp
)

set(GAME_LOGIC_HEADER_FILES
    include/VE_GameLogicAPI.h
    include/VE_GameObject2D.h
)

add_library(VelopraGameLogic ${GAME_LOGIC_SOURCE_FILES} ${GAME_LOGIC_HEADER_FILES})

if(BUILD_SHARED_LIBS)
    target_compile_definitions(VelopraGameLogic PRIVATE BUILDING_GAMELOGIC_DLL)
endif()

target_include_directories(VelopraGameLogic PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(VelopraGameLogic PRIVATE VelopraCore VelopraRenderer)