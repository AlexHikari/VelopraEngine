#include "opengl/VE_OpenGLTexture.h"

namespace velopraEngine {
namespace render {

OpenGLTexture::OpenGLTexture(GLuint id, int width, int height,
                             const std::vector<uint8_t> &data,const std::string& name)
    : textureId(id), width(width), height(height), data(data), name(name) {}

OpenGLTexture::~OpenGLTexture() {
  if (textureId != 0) {
    glDeleteTextures(1, &textureId);
  }
}

unsigned int OpenGLTexture::GetTextureId() const { return textureId; }
int OpenGLTexture::GetWidth() const { return width; }
int OpenGLTexture::GetHeight() const { return height; }
const uint8_t* OpenGLTexture::GetData() const { return data.data(); }
std::string OpenGLTexture::GetName() const { return name; }

} // namespace render
} // namespace velopraEngine