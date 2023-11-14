#include "OpenGLRenderer.h"
#include "VE_Logger.h"

int main() {
	// Initialize the renderer
	OpenGLRenderer renderer;
	VelopraEngine::Core::Logger::Init();
	renderer.Initialize();

	VELOPRA_CORE_INFO("Logger initialized successfully");

	// Main loop
	while (!renderer.WindowShouldClose()) {
		renderer.BeginFrame();
		renderer.RenderFrame();
		renderer.EndFrame();
	}

	// Clean up
	renderer.Shutdown();
	return 0;
}