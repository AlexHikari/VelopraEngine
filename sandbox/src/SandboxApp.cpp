#include "opengl/2d/VE_OpenGL2DRenderer.h"
#include "opengl/2d/VE_OpenGLOrthoCamera.h"
#include "SandboxApp.h"
#include "VE_Event.h"
#include "VE_LoggerMacros.h"
#include "VE_Math.h"
#include "VE_RenderTypes.h"
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
  auto texture = renderer->LoadTexture("wood_crate.png");
  auto gameObject = std::make_shared<velopraEngine::gameLogic::GameObject2D>(
      texture, velopraEngine::core::Vector2(10.0f, 10.0f),
      velopraEngine::core::Vector2(1.0f, 1.0f),
      velopraEngine::core::Vector4(1.0f, 1.0f, 1.0f, 1.0f));

  // Assuming OpenGLOrthoCamera is a subclass of IFollowableCamera
  camera->SetFollowCallback(
      [this](velopraEngine::render::IFollowableCamera &cam,
             float /* deltaTime */) {
        auto orthoCam =
            static_cast<velopraEngine::render::OpenGLOrthoCamera &>(cam);
        if (!gameObjects.empty()) {
          auto gameObject =
              gameObjects
                  .front(); // follow the first gameObject
          auto position = gameObject->GetPosition();
          orthoCam.SetPosition(
              {position.x,
               position.y}); // Update camera position to follow the gameObject
        }
      });

  gameObjects.push_back(gameObject);
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
