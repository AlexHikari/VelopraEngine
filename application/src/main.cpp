#include "UIManager.h"
#include "VE_Logger.h"
#include "VE_LoggerMacros.h"
#include "VE_Core.h"
#include "VE_Time.h"
#include "InputUpdateLayer.h"
#include "WindowManager.h"

int main(int argc, char* argv[]) {
	// Initialize Core and other systems
	auto& core = Core::Instance();
	Logger::Init();
	auto inputUpdateLayer = std::make_shared<InputUpdateLayer>();
	VELOPRA_CORE_INFO("Starting Velopra Engine");

	auto windowManager = std::make_shared<WindowManager>();

	// Initialize and run the UI
	UIManager uiManager(argc, argv, windowManager);
	return uiManager.Run();
}
