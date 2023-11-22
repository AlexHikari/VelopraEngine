#include "QtOpenGLWidget.h"
#include "VE_LoggerMacros.h"
#include <QTimer>

QtOpenGLWidget::QtOpenGLWidget(QWidget *parent,
                               std::shared_ptr<WindowManager> windowManager)
    : QOpenGLWidget(parent), windowManager(windowManager) {

  setMouseTracking(true);
  renderer = new OpenGLRenderer();
  // You can set up a timer for continuous rendering (if needed)
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this,
          QOverload<>::of(&QtOpenGLWidget::update));
  timer->start(16); // approximately 60 fps
  VELOPRA_CORE_INFO("QT OpenGLWidget created");
}

QtOpenGLWidget::~QtOpenGLWidget() {}

void QtOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  if (renderer) {
    renderer->Initialize();
  }
}

void QtOpenGLWidget::resizeGL(int w, int h) {
  if (renderer) {
    renderer->OnWindowSizeChanged(w, h);
  }
}

void QtOpenGLWidget::paintGL() {
  if (renderer) {
    renderer->BeginFrame();
    renderer->RenderFrame();
  }
}

void QtOpenGLWidget::keyPressEvent(QKeyEvent *event) {
  if (windowManager) {
    windowManager->ForwardKeyPressedEvent(event);
  }
  // ... other key press handling
}

void QtOpenGLWidget::mousePressEvent(QMouseEvent *event) {
  if (windowManager) {
    windowManager->ForwardMousePressedEvent(event);
  }
  // ... other mouse press handling
}

void QtOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  if (windowManager) {
    windowManager->ForwardMouseMoveEvent(event);
  }
  // ... other mouse move handling
}