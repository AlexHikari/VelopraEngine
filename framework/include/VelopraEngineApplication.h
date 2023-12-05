#ifndef VELOPRA_ENGINE_APPLICATION_H
#define VELOPRA_ENGINE_APPLICATION_H

#include "VE_Event.h"
#include "VE_EventQueue.h"
#include "VE_GLFWWindow.h"
#include <memory>

namespace velopraEngine {
namespace render {
enum class RenderType;
enum class DimensionType;
class IRenderer;
} // namespace render
namespace framework {

class VelopraEngineApplication {
public:
  VelopraEngineApplication(render::RenderType type,
                           render::DimensionType dimensionType);
  virtual ~VelopraEngineApplication();

  void Run();
  virtual void OnStart() = 0;
  virtual void OnUpdate(float deltaTime) = 0;
  virtual void OnEvent(core::Event &event) = 0;

protected:
  void InitializeWindow(const std::string &title, int width, int height);
  void InitializeRenderer(render::RenderType renderType,
                          render::DimensionType dimensionType, int width,
                          int height);
  void MainLoop();
  void ProcessEvents(core::EventQueue &eventQueue);
  std::shared_ptr<render::IRenderer> renderer;

private:
  std::unique_ptr<window::VE_GLFWWindow> window;
  bool isRunning;
};

} // namespace framework
} // namespace velopraEngine

#endif // VELOPRA_ENGINE_APPLICATION_H
