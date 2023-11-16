#ifndef VE_IRENDERER_H
#define VE_IRENDERER_H

class IRenderer {
		public:
			virtual ~IRenderer() = default;

			virtual void Initialize() = 0;
			virtual void Shutdown() = 0;
			virtual void BeginFrame() = 0;
			virtual void RenderFrame() = 0;
			virtual void EndFrame() = 0;
};

#endif // VE_IRENDERER_H