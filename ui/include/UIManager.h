#ifndef VE_UI_MANAGER_H
#define VE_UI_MANAGER_H

#include "MainWindow.h"
#include <QApplication>

class WindowManager;

class UIManager {
public:
	UIManager(int argc, char* argv[],std::shared_ptr<WindowManager> windowManager);
	int Run();

private:
	QApplication app;
	MainWindow mainWindow;
};

#endif // VE_UI_MANAGER_H
