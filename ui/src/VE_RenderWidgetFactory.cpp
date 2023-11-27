#include "VE_RenderWidgetFactory.h"
#include "VE_WindowManager.h"
#include "VE_QtOpenGLWidget.h"

namespace velopraEngine {
namespace ui {

std::unique_ptr<IRenderWidget>
RenderWidgetFactory::CreateRenderWidget(RenderType type, std::shared_ptr<WindowManager> wM) {
  switch (type) {
  case RenderType::OpenGL:
    return std::make_unique<QtOpenGLWidget>(nullptr,wM);
  default:
    return std::make_unique<QtOpenGLWidget>(nullptr,wM);
  }
}

} // namespace ui
} // namespace velopraEngine