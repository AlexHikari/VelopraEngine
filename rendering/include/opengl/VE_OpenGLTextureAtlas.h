#ifndef VE_OPENGL_TEXTURE_ATLAS_H
#define VE_OPENGL_TEXTURE_ATLAS_H

#include "interfaces/VE_ITexture.h"
#include "interfaces/VE_ITextureLoader.h"
#include "opengl/VE_OpenGLTexture.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace velopraEngine {
namespace render {

class OpenGLTextureAtlas {
public:
  OpenGLTextureAtlas();
  OpenGLTextureAtlas(int width, int height);
  std::shared_ptr<ITexture> GetTexture() const;
  void AddSubTexture(const std::string &name, const glm::vec2 &topLeft,
                     const glm::vec2 &dimensions);
  bool HasSubTexture(const std::string &name) const;
  void AddTexture(const std::string &name, std::shared_ptr<ITexture> texture);
  std::shared_ptr<SubTexture> GetSubTexture(const std::string &name) const;
  void RemoveTexture(const std::string &name);
  void UpdateTexture(const std::string &name,
                     std::shared_ptr<ITexture> texture);
  void DefragmentAtlas();

private:
  class Node {
  public:
    glm::ivec2 position;
    glm::ivec2 size;
    bool occupied;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(int x, int y, int width, int height);
    Node *Insert(int width, int height);
  };
  std::shared_ptr<ITexture> atlasTexture;
  std::unordered_map<std::string, std::shared_ptr<SubTexture>> subTextures;
  std::unique_ptr<Node> root;

  void UpdateAtlasTexture(std::shared_ptr<ITexture> texture,
                          const glm::vec2 &position);
  void ClearNode(Node *node);
  void DefragmentNode(Node *node);
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGL_TEXTURE_ATLAS_H