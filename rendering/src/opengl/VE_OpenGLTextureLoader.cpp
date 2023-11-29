#include "VE_pch.h"
#include "opengl/VE_OpenGLTextureLoader.h"
#include "interfaces/VE_ITextureLoader.h"
#include "opengl/VE_OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace velopraEngine {
namespace render {

std::shared_ptr<ITexture>
OpenGLTextureLoader::LoadTexture(const std::string &filePath) {
  VELOPRA_CORE_INFO("Loading texture: {}", filePath);

  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
  if (!data) {
    VELOPRA_CORE_ERROR("Failed to load texture: {}", filePath);
    return nullptr;
  }

  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Convert the loaded data to a vector for storage in OpenGLTexture
  std::vector<uint8_t> textureData(data, data + (width * height * nrChannels));

  // Free the image data as it's now stored in the textureData vector
  stbi_image_free(data);

  auto texture = std::make_shared<OpenGLTexture>(textureID, width, height,
                                                 textureData, filePath);

  VELOPRA_CORE_INFO("Texture loaded successfully: {}", filePath);
  return texture;
};

} // namespace render
} // namespace velopraEngine
