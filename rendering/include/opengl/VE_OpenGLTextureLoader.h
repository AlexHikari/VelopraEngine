#ifndef VE_OPENGL_TEXTURE_LOADER_H
#define VE_OPENGL_TEXTURE_LOADER_H

#include "VE_RendererAPI.h"
#include "interfaces/VE_ITextureLoader.h"
#include "opengl/VE_OpenGLTexture.h"

namespace velopraEngine {
namespace render {

class VELOPRARENDERER_API OpenGLTextureLoader : public ITextureLoader {
public:

  std::shared_ptr<ITexture> LoadTexture(const std::string &filePath) override;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGL_TEXTURE_LOADER_H