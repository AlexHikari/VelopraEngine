#ifndef VELOPRA_ENGINE_RENDERER_IRENDERER_H
#define VELOPRA_ENGINE_RENDERER_IRENDERER_H

namespace VelopraEngine {
	namespace Renderer {

		class IRenderer {
		public:
			virtual ~IRenderer() = default;

			virtual void Initialize() = 0;
			virtual void Shutdown() = 0;
			virtual void BeginFrame() = 0;
			virtual void RenderFrame() = 0;
			virtual void EndFrame() = 0;
		};

	} // namespace Renderer
} // namespace VelopraEngine

#endif // VELOPRA_ENGINE_RENDERER_IRENDERER_H