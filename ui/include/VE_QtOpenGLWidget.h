#ifndef VE_QT_OPENGL_WIDGET_H
#define VE_QT_OPENGL_WIDGET_H

#include "VE_IRenderWidget.h"
#include "VE_UIApi.h"
#include "VE_WindowManager.h"
#include "interfaces/VE_IRenderer.h"
#include <GL/glew.h>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <memory>

namespace velopraEngine {
namespace ui {

class VELOPRAUI_API QtOpenGLWidget : public QOpenGLWidget,
                                     protected QOpenGLFunctions,
                                     public IRenderWidget {
  Q_OBJECT

public:
  QtOpenGLWidget(QWidget *parent = nullptr,
                 std::shared_ptr<WindowManager> windowManager = nullptr,
                 bool use2DRenderer = false);
  ~QtOpenGLWidget();

  void InitializeRenderer() override;
  void ResizeRenderer(int width, int height) override;
  void Render() override;

  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void showEvent(QShowEvent *event) override;

public slots:
  void initializeRenderer();

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

private:
  std::shared_ptr<render::IRenderer> renderer;
  std::shared_ptr<WindowManager> windowManager;
  bool use2D;
};

} // namespace ui
} // namespace velopraEngine

#endif // VE_QT_OPENGL_WIDGET_H
