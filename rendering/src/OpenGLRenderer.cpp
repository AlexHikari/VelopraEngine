#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "OpenGLRenderer.h"
#include <iostream>

OpenGLRenderer::OpenGLRenderer() : window(nullptr) {
	// Constructor logic is usually empty
}

OpenGLRenderer::~OpenGLRenderer() {
	for (auto& pair : textureCache) {
		glDeleteTextures(1, &pair.second);
	}
	Shutdown();
}

void OpenGLRenderer::Initialize() {
	// Initialize GLFW
	if (!glfwInit()) {
		VELOPRA_CORE_ERROR("Failed to initialize GLFW");
		return;
	}

	// Set window hints for the OpenGL version and profile you are targeting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
	if (!window) {
		VELOPRA_CORE_ERROR("Failed to create GLFW window");
		glfwTerminate();
		return;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;  // Needed for core profile
	if (glewInit() != GLEW_OK) {
		VELOPRA_CORE_ERROR("Failed to initialize GLEW");
		return;
	}

	// Additional OpenGL setup can be done here...
}

void OpenGLRenderer::Shutdown() {
	if (window) {
		glfwDestroyWindow(window);
		window = nullptr;
	}
	glfwTerminate();
}

void OpenGLRenderer::BeginFrame() {
	// Set the clear color and depth
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::RenderFrame() {
	// Bind shader programs, set uniforms, bind VAOs, and draw
}

void OpenGLRenderer::EndFrame() {
	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Poll for and process events
	glfwPollEvents();
}

GLuint OpenGLRenderer::LoadTexture(const std::string& filePath) {

	auto it = textureCache.find(filePath);
	if (it != textureCache.end()) {
		VELOPRA_CORE_TRACE("Texture loaded from cache");
		return it->second;
	}

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		VELOPRA_CORE_ERROR("Failed to load texture: {}", filePath);
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Upload the texture data
	GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps for the texture
	stbi_image_free(data);
	textureCache[filePath] = textureID;

	return textureID;
}

bool OpenGLRenderer::WindowShouldClose() const {
	if (window) {
		return glfwWindowShouldClose(window);
	}
	return true; // If no window exists, signal to close
}
