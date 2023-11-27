#ifndef VE_IRENDER_WIDGET_H
#define VE_IRENDER_WIDGET_H

#include "VE_UIApi.h"
#include <QWidget>

namespace velopraEngine {
namespace ui {

class VELOPRAUI_API IRenderWidget {
public:
  virtual ~IRenderWidget() = default;

  virtual void InitializeRenderer() = 0;
  virtual void ResizeRenderer(int width, int height) = 0;
  virtual void Render() = 0;
  // Add other necessary virtual functions here
};

} // namespace ui
} // namespace velopraEngine

#endif // VE_IRENDER_WIDGET_H
