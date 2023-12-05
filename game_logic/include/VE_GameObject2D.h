#ifndef VE_GAMEOBJECT2D_H
#define VE_GAMEOBJECT2D_H

#include "VE_GameLogicAPI.h"
#include "VE_Math.h"
#include <memory>

namespace velopraEngine {

namespace render {
class ITexture;
class IRenderer2D;
} // namespace render
namespace gameLogic {

class VELOPRAGAMELOGIC_API GameObject2D {
public:
  GameObject2D(std::shared_ptr<render::ITexture> texture,
               const core::Vector2 &position, const core::Vector2 &size,
               const core::Vector4 &color);
  virtual ~GameObject2D() = default;

  virtual void Update(float deltaTime);
  virtual void Render(render::IRenderer2D &renderer);

  void SetPosition(const core::Vector2 &newPosition);
  core::Vector2 GetPosition() const;

  void SetSize(const core::Vector2 &newSize);
  core::Vector2 GetSize() const;

  void SetColor(const core::Vector4 &newColor);
  core::Vector4 GetColor() const;

  void SetRotation(float newRotation);
  float GetRotation() const;

  void SetVelocity(const core::Vector2 &newVelocity);
  core::Vector2 GetVelocity() const;

  void SetVisible(bool isVisible);
  bool IsVisible() const;

  // Additional methods for interactions, collisions, etc.

private:
  std::shared_ptr<render::ITexture> texture;
  core::Vector2 position;
  core::Vector2 size;
  core::Vector4 color;
  float rotation;
  core::Vector2 velocity;
  bool visible;
};

} // namespace gameLogic
} // namespace velopraEngine

#endif // VE_GAMEOBJECT2D_H
