#include "VE_pch.h"

#include "opengl/2d/VE_OpenGL2DRenderer.h"
#include "opengl/2d/VE_OpenGLOrthoCamera.h"
#include "opengl/VE_OpenGLShader.h"
#include "opengl/VE_OpenGLTextureAtlas.h"

namespace velopraEngine {
namespace render {

OpenGL2DRenderer::OpenGL2DRenderer(
    std::shared_ptr<OpenGLTextureLoader> textureLoader, int windowWidth,
    int windowHeight)
    : textureLoader(textureLoader), windowWidth(windowWidth),
      windowHeight(windowHeight) {
  // Constructor initialization
}

OpenGL2DRenderer::~OpenGL2DRenderer() {
  // Destructor for cleaning up resources
}

void OpenGL2DRenderer::Initialize() {
  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    VELOPRA_CORE_ERROR("Failed to initialize GLEW.");
    return;
  }

  // Set up OpenGL options
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Initialize shader program
  shader = std::make_unique<OpenGLShader>("vertex_shader.glsl",
                                          "fragment_shader.glsl");

  float leftBoundary = 0.0f;
  float rightBoundary = static_cast<float>(windowWidth);
  float bottomBoundary = static_cast<float>(windowHeight);
  float topBoundary = 0.0f;
  camera = std::make_unique<OpenGLOrthoCamera>(leftBoundary, rightBoundary,
                                               bottomBoundary, topBoundary);

  SetupBatchRendering();
}

void OpenGL2DRenderer::BeginFrame() {
  // Clear the screen
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Start a new batch
  StartBatch();
}

void OpenGL2DRenderer::RenderFrame() {
  // Bind shader
  shader->Bind();

  // Set up projection matrix from the camera
  shader->SetUniformMat4f("u_Projection", camera->GetProjectionMatrix());

  // Render batched sprites/shapes
  FlushBatch();

  // Unbind shader
  shader->Unbind();
}

std::shared_ptr<ITexture>
OpenGL2DRenderer::LoadTexture(const std::string &filePath) {
  VELOPRA_CORE_INFO("Requesting texture load: {}", filePath);

  // Check if the texture is already in the atlas
  if (textureAtlas->HasSubTexture(filePath)) {
    VELOPRA_CORE_TRACE("Texture already in atlas");
    return textureAtlas->GetTexture(); // Return the atlas texture
  }

  // Load the texture and add it to the atlas
  auto texture = textureLoader->LoadTexture(filePath);
  if (!texture) {
    VELOPRA_CORE_ERROR("Failed to load texture: {}", filePath);
    return nullptr;
  }

  // Add the texture to the atlas
  textureAtlas->AddTexture(filePath, texture);

  VELOPRA_CORE_INFO("Texture added to atlas: {}", filePath);
  return textureAtlas->GetTexture();
}

void OpenGL2DRenderer::SetupBatchRendering() {
  // Initialize VAO, VBO, etc. for batch rendering
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Allocate enough memory for MAX_BATCH_SIZE quads (6 vertices per quad)
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * 6 * MAX_BATCH_SIZE,
               nullptr, GL_DYNAMIC_DRAW);

  // Set up vertex attribute pointers...
  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                        (void *)offsetof(VertexData, position));
  glEnableVertexAttribArray(0);
  // Texture coordinate attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                        (void *)offsetof(VertexData, texCoords));
  glEnableVertexAttribArray(1);
  // Texture ID attribute
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                        (void *)offsetof(VertexData, texId));
  glEnableVertexAttribArray(2);
  // Color attribute
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                        (void *)offsetof(VertexData, color));
  glEnableVertexAttribArray(3);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void OpenGL2DRenderer::StartBatch() {
  currentBatch->vertices.clear();
  currentBatch->indices.clear();
  currentBatch->numVertices = 0;
  currentBatch->numIndices = 0;
}

void OpenGL2DRenderer::FlushBatch() {
  if (currentBatch->numVertices == 0)
    return; // Nothing to draw

  // Bind the VAO
  glBindVertexArray(VAO);

  // Upload the accumulated vertex data to the GPU
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0,
                  currentBatch->vertices.size() * sizeof(VertexData),
                  currentBatch->vertices.data());

  // Bind the texture atlas
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureAtlas->GetTexture()->GetTextureId());

  // Draw call
  glDrawArrays(GL_TRIANGLES, 0, currentBatch->numVertices);

  // Unbind VAO
  glBindVertexArray(0);

  StartBatch(); // Prepare for the next batch
}

void OpenGL2DRenderer::NextBatch() {
  FlushBatch();
  StartBatch();
}

void OpenGL2DRenderer::AddQuad(const glm::vec2 &position, const glm::vec2 &size,
                               const glm::vec4 &color,
                               std::shared_ptr<ITexture> texture) {
  if (currentBatch->numVertices + 6 > MAX_BATCH_SIZE) {
    FlushBatch(); // Flush and start a new batch if the current one is full
  }

  // Calculate texture coordinates
  glm::vec2 texCoords[4];
  if (texture) {
    auto subTexture = textureAtlas->GetSubTexture(texture->GetName());
    texCoords[0] = subTexture->GetTexCoords(0);
    texCoords[1] = subTexture->GetTexCoords(1);
    texCoords[2] = subTexture->GetTexCoords(2);
    texCoords[3] = subTexture->GetTexCoords(3);
  } else {
    // Default texture coordinates for no texture
    texCoords[0] = glm::vec2(0.0f, 0.0f);
    texCoords[1] = glm::vec2(1.0f, 0.0f);
    texCoords[2] = glm::vec2(1.0f, 1.0f);
    texCoords[3] = glm::vec2(0.0f, 1.0f);
  }

  // Calculate vertex positions
  glm::vec2 vertices[4];
  vertices[0] = position;                                   // Top-left
  vertices[1] = glm::vec2(position.x + size.x, position.y); // Top-right
  vertices[2] =
      glm::vec2(position.x + size.x, position.y + size.y);  // Bottom-right
  vertices[3] = glm::vec2(position.x, position.y + size.y); // Bottom-left

  // Add vertex data to the batch
  for (int i = 0; i < 4; ++i) {
    currentBatch->vertices.push_back(VertexData{
        vertices[i],                           // Position
        texCoords[i],                          // Texture coordinates
        texture ? texture->GetTextureId() : 0, // Texture ID
        color                                  // Color
    });
  }

  // Define indices for two triangles that make up the quad
  unsigned int offset = currentBatch->numVertices;
  unsigned int indices[] = {offset, offset + 1, offset + 2,
                            offset, offset + 2, offset + 3};
  currentBatch->indices.insert(currentBatch->indices.end(), std::begin(indices),
                               std::end(indices));

  currentBatch->numVertices += 6; // 6 vertices for a quad (2 triangles)
}

void OpenGL2DRenderer::OnWindowSizeChanged(int width, int height) {
  windowWidth = width;
  windowHeight = height;

  // Update the viewport
  glViewport(0, 0, width, height);

  if (auto orthoCamera = dynamic_cast<OpenGLOrthoCamera *>(camera.get())) {
    float leftBoundary = 0.0f;
    float rightBoundary = static_cast<float>(width);
    float bottomBoundary = static_cast<float>(height);
    float topBoundary = 0.0f;
    orthoCamera->SetOrthoBounds(leftBoundary, rightBoundary, bottomBoundary,
                                topBoundary);
  }
}

} // namespace render
} // namespace velopraEngine
