#ifndef VE_RENDER_API_H
#define VE_RENDER_API_H

#ifdef _WIN32
#ifdef BUILDING_RENDERER_DLL
#define VELOPRARENDERER_API __declspec(dllexport)
#else
#define VELOPRARENDERER_API __declspec(dllimport)
#endif
#else
#define VELOPRARENDERER_API
#endif

#endif // VE_RENDER_API_H