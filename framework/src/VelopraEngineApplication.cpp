#include "opengl/2d/VE_OpenGL2DRenderer.h"
#include "Opengl/3d/VE_OpenGLRenderer.h"
#include "opengl/2d/VE_OpenGLOrthoCamera.h"
#include "opengl/3d/VE_OpenGLCamera.h"
#include "VelopraEngineApplication.h"
#include "VE_Core.h"
#include "VE_InputEventGenerator.h"
#include "VE_LoggerMacros.h"
#include "VE_RenderTypes.h"
#include "VE_Time.h"
#include "interfaces/VE_IRenderer.h"

namespace velopraEngine {
namespace framework {

VelopraEngineApplication::VelopraEngineApplication(
    render::RenderType renderType, render::DimensionType dimensionType)
    : isRunning(false) {
  core::Logger::Init();
  InitializeWindow("Main window", 800, 600);
  InitializeRenderer(renderType, dimensionType, 800, 600);
  InitializeCamera(renderType, dimensionType, 800, 600);
}

VelopraEngineApplication::~VelopraEngineApplication() {}

void VelopraEngineApplication::OnStart() {
  // perform any initialization that is
  // common across all applications derived from VelopraEngineApplication.
  VELOPRA_CORE_INFO("VelopraEngineApplication started");
}

void VelopraEngineApplication::OnUpdate(float deltaTime) {
  // handle tasks that need to be updated every frame in all applications,
  // like updating the window or processing input events.
  window->Update();
}

void VelopraEngineApplication::OnEvent(core::Event &event) {
  // process events that are common to all applications, such as window close
  // events.
  if (event.GetEventType() == core::EventType::WindowClose) {
    isRunning = false;
  }
}

void VelopraEngineApplication::Run() {
  OnStart();
  MainLoop();
}

void VelopraEngineApplication::InitializeWindow(const std::string &title,
                                                int width, int height) {
  window = std::make_unique<window::VE_GLFWWindow>();
  window->Initialize(title, width, height);
  window->SetEventCallback(
      [this](std::shared_ptr<core::Event> event) { OnEvent(*event); });
}

void VelopraEngineApplication::InitializeRenderer(
    render::RenderType renderType, render::DimensionType dimensionType,
    int width, int height) {
  switch (renderType) {
  case render::RenderType::OpenGL: {
    std::shared_ptr<render::OpenGLTextureLoader> textureLoader =
        std::make_shared<render::OpenGLTextureLoader>();
    if (dimensionType == render::DimensionType::TwoD) {
      renderer = std::make_unique<render::OpenGL2DRenderer>(textureLoader,
                                                            width, height);
    } else if (dimensionType == render::DimensionType::ThreeD) {
      renderer = std::make_unique<render::OpenGLRenderer>(width, height);
    }
    if (renderer) {
      renderer->Initialize();
    }
  } break;
  case render::RenderType::Vulkan:
    break;
  case render::RenderType::DirectX:
    break;
  case render::RenderType::Metal:
    break;
  default:
    VELOPRA_CORE_ERROR("Unsupported renderer type");
  }
}

void VelopraEngineApplication::InitializeCamera(
    render::RenderType renderType, render::DimensionType dimensionType,
    int width, int height) {
  switch (renderType) {
  case render::RenderType::OpenGL: {
    if (dimensionType == render::DimensionType::TwoD) {
      camera = std::make_shared<render::OpenGLOrthoCamera>(
          0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
    } else if (dimensionType == render::DimensionType::ThreeD) {
      // camera = std::make_unique<render::OpenGLCamera>(width, height);
    }
  } break;
  case render::RenderType::Vulkan:
    break;
  case render::RenderType::DirectX:
    break;
  case render::RenderType::Metal:
    break;
  default:
    VELOPRA_CORE_ERROR("Unsupported renderer type");
  }
}

void VelopraEngineApplication::MainLoop() {
  isRunning = true;
  auto &time = core::Time::Instance();
  auto eventQueue = core::Core::Instance().GetEventQueue();
  auto &inputEventGenerator = input::InputEventGenerator::Instance();

  while (isRunning && !window->ShouldClose()) {
    time.Update();
    float deltaTime = static_cast<float>(time.GetDeltaTime());
    ProcessEvents(*eventQueue);
    inputEventGenerator.Update();

    OnUpdate(deltaTime);
    camera->Update(deltaTime);

    // Update rendering
    renderer->BeginFrame();
    renderer->RenderFrame();
  }
}

void VelopraEngineApplication::ProcessEvents(core::EventQueue &eventQueue) {
  eventQueue.ProcessEvents();
}

} // namespace framework
} // namespace velopraEngine
