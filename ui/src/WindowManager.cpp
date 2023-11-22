#include "WindowManager.h"
#include "VE_Core.h"
#include "VE_Event.h"
#include "VE_KeyboardEvent.h"
#include "VE_LoggerMacros.h"
#include "VE_MouseEvent.h"

WindowManager::WindowManager() {
  // Constructor implementation
}

WindowManager::~WindowManager() {
  // Destructor implementation
}

void WindowManager::ForwardKeyPressedEvent(QKeyEvent *event) {
  std::shared_ptr<Event> veEvent;

  if (event->type() == QEvent::KeyPress) {
    veEvent = std::make_shared<KeyPressedEvent>(event->key(), 0);
    VELOPRA_CORE_INFO("keyPressed");
  } else if (event->type() == QEvent::KeyRelease) {
    veEvent = std::make_shared<KeyReleasedEvent>(event->key());
    VELOPRA_CORE_INFO("keyReleased");
  }

  if (veEvent) {
    Core::Instance().GetEventQueue()->PushEvent(veEvent);
  }
}

void WindowManager::ForwardMouseMoveEvent(QMouseEvent *event) {
  auto veEvent = std::make_shared<MouseMovedEvent>(event->x(), event->y());
  VELOPRA_CORE_INFO("Mouse moved coords X:{} Y:{}", event->x(), event->y());
  Core::Instance().GetEventQueue()->PushEvent(veEvent);
}

void WindowManager::ForwardMousePressedEvent(QMouseEvent *event) {
  std::shared_ptr<Event> veEvent;
  if (event->type() == QEvent::MouseButtonPress) {
    veEvent = std::make_shared<MouseButtonPressedEvent>(event->button());
    VELOPRA_CORE_INFO("MousePressed");
  } else if (event->type() == QEvent::MouseButtonRelease) {
    veEvent = std::make_shared<MouseButtonReleasedEvent>(event->button());
    VELOPRA_CORE_INFO("MouseReleased");
  }
  if (veEvent) {
    Core::Instance().GetEventQueue()->PushEvent(veEvent);
  }
}

void WindowManager::RegisterWindowSizeObserver(IWindowSizeObserver *observer) {
  sizeObservers.push_back(observer);
}

void WindowManager::UnregisterWindowSizeObserver(
    IWindowSizeObserver *observer) {
  sizeObservers.erase(
      std::remove(sizeObservers.begin(), sizeObservers.end(), observer),
      sizeObservers.end());
}

void WindowManager::NotifyWindowSizeChanged(int width, int height) {
  for (auto *observer : sizeObservers) {
    observer->OnWindowSizeChanged(width, height);
  }
}
