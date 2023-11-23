#include "VE_RenderWidgetFactory.h"
#include "VE_QtOpenGLWidget.h"

namespace velopraEngine {
namespace ui {

std::unique_ptr<IRenderWidget>
RenderWidgetFactory::CreateRenderWidget(RenderType type) {
  switch (type) {
  case RenderType::OpenGL:
    return std::make_unique<QtOpenGLWidget>();
  default:
    return std::make_unique<QtOpenGLWidget>();
  }
}

} // namespace ui
} // namespace velopraEngine