#ifndef VE_OPENGL_TEXTURE_H
#define VE_OPENGL_TEXTURE_H

#include "interfaces/VE_ITexture.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace velopraEngine {
namespace render {

class SubTexture {
public:
  SubTexture(std::shared_ptr<ITexture> texture, const glm::vec2 &topLeft,
             const glm::vec2 &dimensions)
      : texture(texture), topLeft(topLeft), dimensions(dimensions) {}

  SubTexture()
      : texture(nullptr), topLeft(glm::vec2(0.0f, 0.0f)),
        dimensions(glm::vec2(0.0f, 0.0f)) {}

  std::shared_ptr<ITexture> GetTexture() const { return texture; }

  glm::vec2 GetTexCoords(int cornerIndex) const {
    // Calculate normalized texture coordinates
    float x = topLeft.x + (cornerIndex % 2) * dimensions.x;
    float y = topLeft.y + (cornerIndex / 2) * dimensions.y;
    return glm::vec2(x, y);
  }
  glm::vec2 gettopLeft() const { return topLeft; }
  glm::vec2 getDimensions() const { return dimensions; }

private:
  std::shared_ptr<ITexture> texture;
  glm::vec2 topLeft;
  glm::vec2 dimensions;
};

class OpenGLTexture : public ITexture {
public:
  OpenGLTexture(GLuint id, int width, int height,
                const std::vector<uint8_t> &data, const std::string& name);

  ~OpenGLTexture();

  virtual unsigned int GetTextureId() const override;
  int GetWidth() const override;
  int GetHeight() const override;
  const uint8_t* GetData() const override;
  std::string GetName() const override;

private:
  GLuint textureId;
  std::string name;
  int width;
  int height;
  std::vector<uint8_t> data;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGL_TEXTURE_H
