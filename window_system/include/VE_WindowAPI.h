#ifndef VE_WINDOW_API_H
#define VE_WINDOW_API_H

#ifdef _WIN32
#ifdef BUILDING_WINDOWSYSTEM_DLL
#define VELOPRAWINDOW_API __declspec(dllexport)
#else
#define VELOPRAWINDOW_API __declspec(dllimport)
#endif
#else
#define VELOPRAWINDOW_API
#endif

#endif // VE_CORE_API_H