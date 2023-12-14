#include "VE_GameObject2D.h"
#include "interfaces/VE_IRenderer2D.h"
#include "interfaces/VE_ITexture.h"

namespace velopraEngine {
namespace gameLogic {

GameObject2D::GameObject2D(std::shared_ptr<render::ITexture> texture,
                           const core::Vector2 &position,
                           const core::Vector2 &size,
                           const core::Vector4 &color)
    : texture(texture), position(position), size(size), color(color),
      rotation(0.0f), velocity(0.0f, 0.0f), visible(true) {}

void GameObject2D::Update(float deltaTime) {
  // Update logic for the game object (e.g., movement, animation)
  // position = position + velocity * deltaTime;
  // Additional update logic...
}

void GameObject2D::Render(std::shared_ptr<render::IRenderer2D> renderer) {
  if (visible) {
    renderer->AddQuad(position, size, color, rotation,
                     texture); // Assuming AddQuad handles rotation
  }
}

void GameObject2D::SetPosition(const core::Vector2 &newPosition) {
  position = newPosition;
}

core::Vector2 GameObject2D::GetPosition() const { return position; }

void GameObject2D::SetSize(const core::Vector2 &newSize) { size = newSize; }

core::Vector2 GameObject2D::GetSize() const { return size; }

void GameObject2D::SetColor(const core::Vector4 &newColor) { color = newColor; }

core::Vector4 GameObject2D::GetColor() const { return color; }

void GameObject2D::SetRotation(float newRotation) { rotation = newRotation; }

float GameObject2D::GetRotation() const { return rotation; }

void GameObject2D::SetVelocity(const core::Vector2 &newVelocity) {
  velocity = newVelocity;
}

core::Vector2 GameObject2D::GetVelocity() const { return velocity; }

void GameObject2D::SetVisible(bool isVisible) { visible = isVisible; }

bool GameObject2D::IsVisible() const { return visible; }

} // namespace gameLogic
} // namespace velopraEngine
