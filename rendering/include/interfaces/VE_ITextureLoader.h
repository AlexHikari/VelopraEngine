#ifndef VE_ITEXTURE_LOADER_H
#define VE_ITEXTURE_LOADER_H

#include "VE_ITexture.h"
#include <memory>
#include <string>

namespace velopraEngine {
namespace render {

class ITextureLoader {
public:
  virtual ~ITextureLoader() = default;
  virtual std::shared_ptr<ITexture>
  LoadTexture(const std::string &filePath) = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_ITEXTURE_LOADER_H