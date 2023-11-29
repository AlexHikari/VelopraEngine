#ifndef VE_TEXTURE_H
#define VE_TEXTURE_H

#include "VE_RendererAPI.h"

namespace velopraEngine {
namespace render {

class VELOPRARENDERER_API ITexture {
public:
  virtual ~ITexture() = default;

  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;
  virtual const uint8_t *GetData() const = 0;
  virtual unsigned int GetTextureId() const = 0;
  virtual std::string GetName() const = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_TEXTURE_H
