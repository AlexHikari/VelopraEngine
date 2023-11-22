// RendererAPI.h
#ifdef _WIN32
#ifdef BUILDING_RENDERER_DLL
#define RENDERER_API __declspec(dllexport)
#else
#define RENDERER_API __declspec(dllimport)
#endif
#else
#define RENDERER_API
#endif