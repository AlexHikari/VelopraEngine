#include "VE_LoggerMacros.h"
#include "VE_Event.h"
#include "VE_RenderTypes.h"
#include "opengl/2d/VE_OpenGL2DRenderer.h"
#include "SandboxApp.h"
#include "VE_Math.h"
#include <memory>


SandboxApp::SandboxApp()
    : VelopraEngineApplication(velopraEngine::render::RenderType::OpenGL,
                               velopraEngine::render::DimensionType::TwoD) {
  // Initialization specific to the sandbox application
  InitializeGameObjects();
}

SandboxApp::~SandboxApp() {
  // Cleanup
}

 void SandboxApp::InitializeGameObjects() {
  auto texture = renderer->LoadTexture("path/to/texture.png");
  auto gameObject = std::make_unique<velopraEngine::gameLogic::GameObject2D>(
      texture, velopraEngine::core::Vector2(10.0f, 10.0f),
      velopraEngine::core::Vector2(1.0f, 1.0f),
      velopraEngine::core::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
  gameObjects.push_back(std::move(gameObject));
 }

void SandboxApp::OnStart() {
  // Called once at the start
  VELOPRA_INFO("SandboxApp started");
  velopraEngine::framework::VelopraEngineApplication::OnStart();
  // Load resources, initialize game objects, etc.
}

void SandboxApp::OnUpdate(float deltaTime) {
  velopraEngine::framework::VelopraEngineApplication::OnUpdate(deltaTime);
  // Game update logic
  // Example: Update game objects, handle input, etc.
  for (auto &gameObject : gameObjects) {
    gameObject->Update(deltaTime);
  }
  // Render each GameObject2D
  renderer->BeginFrame();
  auto renderer2D =
      std::dynamic_pointer_cast<velopraEngine::render::IRenderer2D>(renderer);
  if (renderer2D) {
    for (auto &gameObject : gameObjects) {
      gameObject->Render(renderer2D);
    }
  }
  renderer->RenderFrame();
}

void SandboxApp::OnEvent(velopraEngine::core::Event &event) {
  velopraEngine::framework::VelopraEngineApplication::OnEvent(event);
  // Handle events
  // Example: Input handling, window resize, etc.
}