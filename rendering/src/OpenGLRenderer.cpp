#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "OpenGLRenderer.h"
#include "OpenGLTexture.h"
#include "pch.h"
#include "stb_image.h"

OpenGLRenderer::OpenGLRenderer()
    : shader(nullptr), model(nullptr), camera(nullptr), aspectRatio(0.0f),
      projectionMatrix(
          glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f)) {}

void OpenGLRenderer::Initialize() {

  glewExperimental = GL_TRUE; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    VELOPRA_CORE_ERROR("Failed to initialize GLEW");
    return;
  }

  camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
  shader =
      std::make_unique<Shader>("vertex_shader.glsl", "fragment_shader.glsl");
  model = std::make_unique<Model>("model.obj", *this);
  model->GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, -1.0f));

  aspectRatio = 800.0f / 600.0f;

  UpdateProjectionMatrix(800, 600);
  VELOPRA_CORE_INFO("OpenGL Renderer initialized successfully.");
}

void OpenGLRenderer::BeginFrame() {
  // Set the clear color and depth
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::RenderFrame() {
  glEnable(GL_DEPTH_TEST);

  // Bind shader
  shader->Bind();
  if (!shader->ValidateProgram()) {
    VELOPRA_CORE_ERROR("Shader program validation failed.");
    return;
  }

  // Get and log matrices
  glm::mat4 view = camera->GetViewMatrix();
  glm::mat4 modelMatrix = model->GetTransform().GetModelMatrix();
  glm::mat4 projection = projectionMatrix;

  // Set uniforms
  shader->SetUniformMat4f("u_Model", modelMatrix);
  shader->SetUniformMat4f("u_View", view);
  shader->SetUniformMat4f("u_Projection", projection);

  model->Draw();

  // Unbind shader
  shader->Unbind();
}

std::shared_ptr<ITexture>
OpenGLRenderer::LoadTexture(const std::string &filePath) {
  VELOPRA_CORE_INFO("Loading texture: {}", filePath);

  auto it = textureCache.find(filePath);
  if (it != textureCache.end()) {
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

  auto texture = std::make_shared<OpenGLTexture>(textureID);
  textureCache[filePath] = texture;

  VELOPRA_CORE_INFO("Texture loaded successfully: {}", filePath);
  return texture;
}

void OpenGLRenderer::OnWindowSizeChanged(int width, int height) {
  // Handle window size change, e.g., update projection matrix
  UpdateProjectionMatrix(width, height);
}

void OpenGLRenderer::UpdateProjectionMatrix(int width, int height) {

  aspectRatio = static_cast<float>(width) / static_cast<float>(height);
  projectionMatrix =
      glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
  // Update viewport as well
  glViewport(0, 0, width, height);
}

#endif