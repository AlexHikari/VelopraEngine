#include "VE_RenderWidgetFactory.h"
#include "VE_QtOpenGLWidget.h"
#include "VE_WindowManager.h"

namespace velopraEngine {
namespace ui {

std::unique_ptr<IRenderWidget>
RenderWidgetFactory::CreateRenderWidget(render::RenderType type,
                                        std::shared_ptr<WindowManager> wM) {
  switch (type) {
  case render::RenderType::OpenGL:
    return std::make_unique<QtOpenGLWidget>(nullptr, wM);
  default:
    return std::make_unique<QtOpenGLWidget>(nullptr, wM);
  }
}

} // namespace ui
} // namespace velopraEngine