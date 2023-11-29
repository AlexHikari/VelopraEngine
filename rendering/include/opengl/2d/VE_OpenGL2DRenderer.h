#ifndef VE_OPENGL_2D_RENDERER_H
#define VE_OPENGL_2D_RENDERER_H

#include "interfaces/VE_ICamera.h"
#include "interfaces/VE_IRenderer.h"
#include "interfaces/VE_IShader.h"
#include "interfaces/VE_ITexture.h"
#include "opengl/VE_OpenGLTextureAtlas.h"
#include "opengl/VE_OpenGLTextureLoader.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace velopraEngine {
namespace render {

class VELOPRARENDERER_API OpenGL2DRenderer : public IRenderer {
public:
  static constexpr size_t MAX_BATCH_SIZE = 1000;
  OpenGL2DRenderer(std::shared_ptr<OpenGLTextureLoader> textureLoader,
                   int windowWidth, int windowHeight);
  ~OpenGL2DRenderer() override;

  void Initialize() override;
  void BeginFrame() override;
  void RenderFrame() override;
  std::shared_ptr<ITexture> LoadTexture(const std::string &filePath) override;
  void AddQuad(const glm::vec2 &position, const glm::vec2 &size,
               const glm::vec4 &color, std::shared_ptr<ITexture> texture);
  void OnWindowSizeChanged(int width, int height) override;

private:
  struct VertexData {
    glm::vec2 position;
    glm::vec2 texCoords;
    unsigned int texId;
    glm::vec4 color;
  };

  struct Batch {
    std::vector<VertexData> vertices;
    std::vector<GLuint> indices;
    unsigned int numVertices = 0;
    unsigned int numIndices = 0;
  };

  std::shared_ptr<OpenGLTextureAtlas> textureAtlas;
  std::unique_ptr<IShader> shader;
  std::unique_ptr<ICamera> camera;
  std::shared_ptr<OpenGLTextureLoader> textureLoader;
  std::unique_ptr<Batch> currentBatch;
  GLuint VAO, VBO;
  int windowWidth;
  int windowHeight;

  void StartBatch();
  void FlushBatch();
  void NextBatch();
  void SetupBatchRendering();
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGL_2D_RENDERER_H
