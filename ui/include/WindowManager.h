#ifndef VE_WINDOW_MANAGER_H
#define VE_WINDOW_MANAGER_H

#include "IWindowSizeObserver.h"
#include "UIApi.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <vector>

class UI_API WindowManager {
public:
  WindowManager();
  ~WindowManager();

  void ForwardKeyPressedEvent(QKeyEvent *event);
  void ForwardMousePressedEvent(QMouseEvent *event);
  void ForwardMouseMoveEvent(QMouseEvent *event);
  void RegisterWindowSizeObserver(IWindowSizeObserver *observer);
  void UnregisterWindowSizeObserver(IWindowSizeObserver *observer);

private:
  std::vector<IWindowSizeObserver *> sizeObservers;

  void NotifyWindowSizeChanged(int width, int height);
};

#endif // VE_WINDOW_MANAGER_H
