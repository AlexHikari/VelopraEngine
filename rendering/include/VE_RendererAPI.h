// RendererAPI.h
#ifdef _WIN32
#ifdef BUILDING_RENDERER_DLL
#define VELOPRARENDERER_API __declspec(dllexport)
#else
#define VELOPRARENDERER_API __declspec(dllimport)
#endif
#else
#define VELOPRARENDERER_API
#endif