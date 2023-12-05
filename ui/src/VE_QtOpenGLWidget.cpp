#include "VE_QtOpenGLWidget.h"
#include "VE_LoggerMacros.h"
#include "opengl/2d/VE_OpenGL2DRenderer.h"
#include "opengl/3d/VE_OpenGLRenderer.h"
#include "opengl/VE_OpenGLTextureLoader.h"
#include <QTimer>

namespace velopraEngine {
namespace ui {

QtOpenGLWidget::QtOpenGLWidget(QWidget *parent,
                               std::shared_ptr<WindowManager> windowManager,
                               render::DimensionType dimensionType)
    : QOpenGLWidget(parent), windowManager(windowManager) {

  if (dimensionType == render::DimensionType::TwoD)
    use2D = true;
  else if (dimensionType == render::DimensionType::ThreeD)
    use2D = false;
  QOpenGLWidget::setMouseTracking(
      true); // This directly calls QOpenGLWidget's setMouseTracking
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this,
          QOverload<>::of(&QtOpenGLWidget::update));
  timer->start(16); // approximately 60 fps
  VELOPRA_CORE_INFO("QT OpenGLWidget created");
}

void QtOpenGLWidget::initializeRenderer() {
  int width = this->width();
  int height = this->height();

  if (use2D) {
    renderer = std::make_shared<render::OpenGL2DRenderer>(
        std::make_shared<render::OpenGLTextureLoader>(), width, height);
  } else {
    renderer = std::make_shared<render::OpenGLRenderer>(width, height);
  }
}

void QtOpenGLWidget::showEvent(QShowEvent *event) {
  QOpenGLWidget::showEvent(event);
  initializeRenderer();
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

void QtOpenGLWidget::InitializeRenderer() {
  // nothing to initialize here
}

void QtOpenGLWidget::ResizeRenderer(int width, int height) {
  resizeGL(width, height);
}

void QtOpenGLWidget::Render() {
  ////nothing to render here
}

} // namespace ui
} // namespace velopraEngine