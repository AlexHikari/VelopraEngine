#ifndef VE_RENDER_WIDGET_FACTORY
#define VE_RENDER_WIDGET_FACTORY

#include "VE_UIApi.h"
#include "VE_IRenderWidget.h"
#include "VE_RenderTypes.h"
#include <memory>

namespace velopraEngine {
namespace ui {

class VELOPRAUI_API RenderWidgetFactory {
public:
  static std::unique_ptr<IRenderWidget> CreateRenderWidget(RenderType type);
};

} // namespace ui
} // namespace velopraEngine

#endif // VE_RENDER_WIDGET_FACTORY


