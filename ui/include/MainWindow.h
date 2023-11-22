#ifndef VE_MAIN_WINDOW_H
#define VE_MAIN_WINDOW_H

#include "QtOpenGLWidget.h"
#include "UIApi.h"
#include <QDockWidget>
#include <QMainWindow>

class WindowManager;

class UI_API MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             std::shared_ptr<WindowManager> windowManager = nullptr);

private:
  QtOpenGLWidget *openGLWidget;
  QDockWidget *leftDockWidget;
  QDockWidget *rightDockWidget;

  bool eventFilter(QObject *object, QEvent *event);
};

#endif // VE_MAIN_WINDOW_H
