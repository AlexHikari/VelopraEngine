#include "VE_pch.h"

#include "opengl/3d/VE_OpenGLRenderer.h"
#include "VE_RenderUtils.h"
#include "opengl/3d/VE_OpenGLCamera.h"
#include "opengl/3d/VE_OpenGLModel.h"
#include "opengl/VE_OpenGLTexture.h"
#include "opengl/VE_OpenGlShader.h"
#include "stb_image.h"

namespace velopraEngine {
namespace render {

OpenGLRenderer::OpenGLRenderer(int width, int height)
    : m_shader(nullptr), m_model(nullptr), m_camera(nullptr),
      m_aspectRatio(0.0f), m_width(width), m_height(height) {
  m_projectionMatrix =
      core::Matrix4::Perspective(45.0f, m_aspectRatio, 0.1f, 100.0f);
}

void OpenGLRenderer::Initialize() {

  glewExperimental = GL_TRUE; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    VELOPRA_CORE_ERROR("Failed to initialize GLEW");
    return;
  }

  m_camera = std::make_unique<OpenGLCamera>(glm::vec3(0.0f, 0.0f, 100.0f));
  m_model = std::make_unique<OpenGLModel>("model.obj", *this);
  m_shader = std::make_unique<OpenGLShader>("vertex_shader.glsl",
                                          "fragment_shader.glsl");

  m_model->GetTransform().SetPosition(core::Vector3(0.0f, 0.0f, -100.0f));

  m_aspectRatio = static_cast<float>(m_width / m_height);

  UpdateProjectionMatrix(m_width, m_height);
  VELOPRA_CORE_INFO("OpenGL Renderer initialized successfully.");
}

void OpenGLRenderer::BeginFrame() {
  // Set the clear color and depth
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::RenderFrame() {
  glEnable(GL_DEPTH_TEST);

  m_shader->Bind();
  if (!m_shader->ValidateProgram()) {
    VELOPRA_CORE_ERROR("Shader program validation failed.");
    return;
  }

  m_shader->SetUniformMat4f("u_Model",
                            m_model->GetTransform().GetModelMatrix());
  m_shader->SetUniformMat4f("u_View", m_camera->GetViewMatrix());
  m_shader->SetUniformMat4f("u_Projection", m_projectionMatrix);

  m_model->Draw();
  m_shader->Unbind();
}

std::shared_ptr<ITexture>
OpenGLRenderer::LoadTexture(const std::string &filePath) {
  VELOPRA_CORE_INFO("Loading texture: {}", filePath);

  auto it = m_textureCache.find(filePath);
  if (it != m_textureCache.end()) {
    VELOPRA_CORE_TRACE("Texture loaded from cache");
    return it->second;
  }

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
  stbi_image_free(data);

  std::vector<uint8_t> textureData(data, data + (width * height * nrChannels));

  auto texture = std::make_shared<OpenGLTexture>(textureID, width, height,
                                                 textureData, filePath);
  m_textureCache[filePath] = texture;

  VELOPRA_CORE_INFO("Texture loaded successfully: {}", filePath);
  return texture;
}

void OpenGLRenderer::OnWindowSizeChanged(int width, int height) {
  // Handle window size change, e.g., update projection matrix
  UpdateProjectionMatrix(width, height);
  m_width = width;
  m_height = height;
}

void OpenGLRenderer::UpdateProjectionMatrix(int width, int height) {
  m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
  m_projectionMatrix = core::Matrix4::Perspective(glm::radians(90.0f),
                                                m_aspectRatio, 0.1f, 100.0f);
  glViewport(0, 0, width, height);
}

} // namespace render
} // namespace velopraEngine