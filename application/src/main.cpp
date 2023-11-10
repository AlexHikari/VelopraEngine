#include "OpenGLRenderer.h"

int main() {
	// Initialize the renderer
	OpenGLRenderer renderer;
	renderer.Initialize();

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