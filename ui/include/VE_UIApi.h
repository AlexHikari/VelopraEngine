#ifndef VE_UI_API_H
#define VE_UI_API_H

#ifdef _WIN32
#ifdef BUILDING_UI_DLL
#define VELOPRAUI_API __declspec(dllexport)
#else
#define VELOPRAUI_API __declspec(dllimport)
#endif
#else
#define VELOPRAUI_API
#endif

#endif // VE_UI_API_H