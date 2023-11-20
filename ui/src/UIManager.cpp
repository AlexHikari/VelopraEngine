#include "UIManager.h"

UIManager::UIManager(int argc, char* argv[], std::shared_ptr<WindowManager> windowManager) : app(argc, argv), mainWindow(nullptr,windowManager) {
	mainWindow.show();
}

int UIManager::Run() {
	return app.exec();
}
