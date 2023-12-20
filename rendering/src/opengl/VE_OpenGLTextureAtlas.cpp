#include "VE_pch.h"
#include "opengl/VE_OpenGLTextureAtlas.h"
#include "opengl/VE_OpenGLTexture.h"

namespace velopraEngine {
namespace render {

OpenGLTextureAtlas::OpenGLTextureAtlas() {}

OpenGLTextureAtlas::OpenGLTextureAtlas(int width, int height) {
  // Generate and bind the atlas texture
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Allocate memory for the atlas texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);

  // Create an empty data vector for the texture
  std::vector<uint8_t> emptyData(width * height * 4, 0); // 4 channels (RGBA)

    // Store the texture in the atlasTexture shared pointer
  atlasTexture = std::make_shared<OpenGLTexture>(textureID, width, height,
                                                 emptyData, "AtlasTexture");

  // Initialize the root node of the atlas
  root = std::make_unique<Node>(0, 0, width, height);
}

OpenGLTextureAtlas::Node::Node(int x, int y, int width, int height)
    : position(x, y), size(width, height), occupied(false) {}

void OpenGLTextureAtlas::AddSubTexture(const std::string &name,
                                       const glm::vec2 &topLeft,
                                       const glm::vec2 &dimensions) {
  // Create a SubTexture object and add it to the map
  subTextures[name] =
      std::make_shared<SubTexture>(atlasTexture, topLeft, dimensions);
}

OpenGLTextureAtlas::Node *OpenGLTextureAtlas::Node::Insert(int width,
                                                           int height) {
  // If this node is occupied, try inserting into its children
  if (occupied) {
    if (left) {
      Node *newNode = left->Insert(width, height);
      if (newNode)
        return newNode;
    }
    if (right) {
      return right->Insert(width, height);
    }
    return nullptr;
  }

  // If the node is too small, return null
  if (size.x < width || size.y < height) {
    return nullptr;
  }

  // If the node is just right, occupy it
  if (size.x == width && size.y == height) {
    occupied = true;
    return this;
  }

  // Otherwise, split this node and create children
  int deltaWidth = size.x - width;
  int deltaHeight = size.y - height;

  if (deltaWidth > deltaHeight) {
    left = std::make_unique<Node>(position.x, position.y, width, size.y);
    right = std::make_unique<Node>(position.x + width, position.y,
                                   size.x - width, size.y);
  } else {
    left = std::make_unique<Node>(position.x, position.y, size.x, height);
    right = std::make_unique<Node>(position.x, position.y + height, size.x,
                                   size.y - height);
  }

  return left->Insert(width, height);
}

std::shared_ptr<ITexture> OpenGLTextureAtlas::GetTexture() const {
  return atlasTexture;
}

bool OpenGLTextureAtlas::HasSubTexture(const std::string &name) const {
  return subTextures.find(name) != subTextures.end();
}

void OpenGLTextureAtlas::AddTexture(const std::string &name,
                                    std::shared_ptr<ITexture> texture) {
  // Find the next available position using the binary tree
  Node *node = root->Insert(texture->GetWidth(), texture->GetHeight());
  if (!node) {
    VELOPRA_CORE_ERROR("No space left in the texture atlas for: {}", name);
    return;
  }

  glm::vec2 position(node->position.x, node->position.y);
  UpdateAtlasTexture(texture, position);

  glm::vec2 dimensions(static_cast<float>(texture->GetWidth()),
                       static_cast<float>(texture->GetHeight()));
  AddSubTexture(name, position, dimensions);
}

void OpenGLTextureAtlas::UpdateAtlasTexture(std::shared_ptr<ITexture> texture,
                                            const glm::vec2 &position) {
  glBindTexture(GL_TEXTURE_2D, atlasTexture->GetTextureId());

  glTexSubImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(position.x),
                  static_cast<GLint>(position.y),
                  static_cast<GLint>(texture->GetWidth()),
                  static_cast<GLint>(texture->GetHeight()), GL_RGBA,
                  GL_UNSIGNED_BYTE, texture->GetData());

  glBindTexture(GL_TEXTURE_2D, 0);
}

std::shared_ptr<SubTexture>
OpenGLTextureAtlas::GetSubTexture(const std::string &name) const {
  auto it = subTextures.find(name);
  if (it != subTextures.end()) {
    return it->second;
  } else {
    VELOPRA_CORE_ERROR("SubTexture not found: {}", name);
    return std::make_shared<SubTexture>(); // Return an empty SubTexture if not
                                           // found
  }
}

void OpenGLTextureAtlas::RemoveTexture(const std::string &name) {
  auto it = subTextures.find(name);
  if (it != subTextures.end()) {
    ClearNode(root.get());
    subTextures.erase(it);
  }
}

void OpenGLTextureAtlas::UpdateTexture(const std::string &name,
                                       std::shared_ptr<ITexture> texture) {
  RemoveTexture(name);
  AddTexture(name, texture);
}

void OpenGLTextureAtlas::DefragmentAtlas() { DefragmentNode(root.get()); }

void OpenGLTextureAtlas::ClearNode(Node *node) {
  if (!node)
    return;
  node->occupied = false;
  ClearNode(node->left.get());
  ClearNode(node->right.get());
}

void OpenGLTextureAtlas::DefragmentNode(Node *node) {
  if (!node)
    return;
  if (node->left && node->right) {
    if (!node->left->occupied && !node->right->occupied) {
      node->left.reset();
      node->right.reset();
    } else {
      DefragmentNode(node->left.get());
      DefragmentNode(node->right.get());
    }
  }
}

} // namespace render
} // namespace velopraEngine