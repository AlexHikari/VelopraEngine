#ifndef VE_GAME_LOGIC_API_H
#define VE_GAME_LOGIC_API_H

#ifdef _WIN32
#ifdef BUILDING_GAMELOGIC_DLL
#define VELOPRAGAMELOGIC_API __declspec(dllexport)
#else
#define VELOPRAGAMELOGIC_API __declspec(dllimport)
#endif
#else
#define VELOPRAGAMELOGIC_API
#endif

#endif // VE_GAME_LOGIC_API_H