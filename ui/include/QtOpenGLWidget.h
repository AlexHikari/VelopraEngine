#ifndef VE_QT_OPENGL_WIDGET_H
#define VE_QT_OPENGL_WIDGET_H

#include "OpenGLRenderer.h"
#include "UIApi.h"
#include "WindowManager.h"
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class UI_API QtOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  QtOpenGLWidget(QWidget *parent = nullptr,
                 std::shared_ptr<WindowManager> windowManager = nullptr);
  ~QtOpenGLWidget();

  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

private:
  OpenGLRenderer *renderer;
  std::shared_ptr<WindowManager> windowManager;
};

#endif // VE_QT_OPENGL_WIDGET_H
