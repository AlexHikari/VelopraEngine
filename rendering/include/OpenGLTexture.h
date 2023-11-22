#ifndef VE_OPENGL_TEXTURE_H
#define VE_OPENGL_TEXTURE_H

#include "ITexture.h"
#include <GL/glew.h>

class OpenGLTexture : public ITexture {
public:
  OpenGLTexture(GLuint id) : textureId(id) {}
  virtual ~OpenGLTexture() {
    if (textureId != 0) {
      glDeleteTextures(1, &textureId);
    }
  }

  GLuint GetTextureId() const { return textureId; }

private:
  GLuint textureId;
};

#endif // VE_OPENGL_TEXTURE_H
