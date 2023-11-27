#ifndef VE_WINDOW_MANAGER_H
#define VE_WINDOW_MANAGER_H

#include "VE_IWindowSizeObserver.h"
#include "VE_UIApi.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <vector>

namespace velopraEngine {
namespace ui {

class VELOPRAUI_API WindowManager {
public:
  WindowManager();
  ~WindowManager();

  void ForwardKeyPressedEvent(QKeyEvent *event);
  void ForwardMousePressedEvent(QMouseEvent *event);
  void ForwardMouseMoveEvent(QMouseEvent *event);
  void RegisterWindowSizeObserver(render::IWindowSizeObserver *observer);
  void UnregisterWindowSizeObserver(render::IWindowSizeObserver *observer);

private:
  std::vector<render::IWindowSizeObserver *> sizeObservers;

  void NotifyWindowSizeChanged(int width, int height);
};

} // namespace ui
} // namespace velopraEngine

#endif // VE_WINDOW_MANAGER_H
