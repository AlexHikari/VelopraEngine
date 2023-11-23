#ifndef VE_INPUT_API_H
#define VE_INPUT_API_H

#ifdef _WIN32
#ifdef BUILDING_VELOPRAINPUT_DLL
#define VELOPRAINPUT_API __declspec(dllexport)
#else
#define VELOPRAINPUT_API __declspec(dllimport)
#endif
#else
#define VELOPRAINPUT_API
#endif

#endif // VE_INPUT_API_H