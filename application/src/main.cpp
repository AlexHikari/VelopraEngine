#include "OpenGLRenderer.h"
#include "VE_Logger.h"
#include "VE_LoggerMacros.h"
#include "VE_Core.h"
#include "InputUpdateLayer.h"

int main() {

	// Initialize Core and other systems
	auto& core = Core::Instance();
	Logger::Init();
	auto inputUpdateLayer = std::make_shared<InputUpdateLayer>();
	VELOPRA_CORE_INFO("Starting Velopra Engine");

	// Initialize the renderer and other components
	OpenGLRenderer renderer;
	renderer.Initialize();

	// Add the InputLayer to the Core's LayerStack
	core.PushLayer(inputUpdateLayer.get());

	// Main loop
	while (!renderer.WindowShouldClose()) {
		renderer.BeginFrame();

		// Update InputManager and process input events
		core.GetEventQueue()->ProcessEvents();

		// Render frame and other logic
		renderer.RenderFrame();

		renderer.EndFrame();
	}

	// Clean up
	renderer.Shutdown();
	
	return 0;
}