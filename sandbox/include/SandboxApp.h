#ifndef SANDBOX_APP_H
#define SANDBOX_APP_H

#include "VE_GameObject2D.h"
#include "interfaces/VE_IFollowableCamera.h"
#include "VelopraEngineApplication.h"

class SandboxApp : public velopraEngine::framework::VelopraEngineApplication {
public:
  SandboxApp();
  ~SandboxApp() override;

protected:
  void OnStart() override;
  void OnUpdate(float deltaTime) override;
  void OnEvent(velopraEngine::core::Event &event) override;
  void InitializeGameObjects();

private:
  std::vector<std::shared_ptr<velopraEngine::gameLogic::GameObject2D>>
      gameObjects;
  std::shared_ptr<velopraEngine::render::IFollowableCamera> camera;
};

#endif // SANDBOX_APP_H