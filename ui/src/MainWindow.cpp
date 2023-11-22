#include "MainWindow.h"
#include "OpenGLRenderer.h"
#include "VE_LoggerMacros.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent,
                       std::shared_ptr<WindowManager> windowManager)
    : QMainWindow(parent) {
  // Central Widget (OpenGL Widget)
  openGLWidget = new QtOpenGLWidget(this, windowManager);
  setCentralWidget(openGLWidget);

  // Left Dock Widget
  leftDockWidget = new QDockWidget(tr("Left Panel"), this);
  leftDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
  leftDockWidget->setWidget(new QLabel("Left Panel Content", leftDockWidget));
  addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget);

  // Right Dock Widget
  rightDockWidget = new QDockWidget(tr("Right Panel"), this);
  rightDockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
  rightDockWidget->setWidget(
      new QLabel("Right Panel Content", rightDockWidget));
  addDockWidget(Qt::RightDockWidgetArea, rightDockWidget);

  this->installEventFilter(this);
  showMaximized();
  VELOPRA_CORE_INFO("QT Main window created");
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
  switch (event->type()) {
  case QEvent::KeyPress: {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    openGLWidget->keyPressEvent(keyEvent);
    break;
  }
  case (QEvent::MouseButtonPress || QEvent::MouseButtonRelease): {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    openGLWidget->mousePressEvent(mouseEvent);
    break;
  }
  case QEvent::MouseMove: {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    openGLWidget->mouseMoveEvent(mouseEvent);
    break;
  }
  default:
    break;
  }
  return QMainWindow::eventFilter(obj, event);
}