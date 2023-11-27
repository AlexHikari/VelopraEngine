#ifndef VE_CORE_API_H
#define VE_CORE_API_H

#ifdef _WIN32
#ifdef BUILDING_VELOPRACORE_DLL
#define VELOPRACORE_API __declspec(dllexport)
#else
#define VELOPRACORE_API __declspec(dllimport)
#endif
#else
#define VELOPRACORE_API
#endif

#endif // VE_CORE_API_H