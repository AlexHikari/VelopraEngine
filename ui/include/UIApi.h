// RendererAPI.h
#ifdef _WIN32
#ifdef BUILDING_UI_DLL
#define UI_API __declspec(dllexport)
#else
#define UI_API __declspec(dllimport)
#endif
#else
#define UI_API
#endif