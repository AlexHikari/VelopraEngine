#ifndef VE_FRAMEWORK_API_H
#define VE_FRAMEWORK_API_H

#ifdef _WIN32
#ifdef BUILDING_FRAMEWORK_DLL
#define VELOPRAFRAMEWORK_API __declspec(dllexport)
#else
#define VELOPRAFRAMEWORK_API __declspec(dllimport)
#endif
#else
#define VELOPRAFRAMEWORK_API
#endif

#endif // VE_FRAMEWORK_API_H