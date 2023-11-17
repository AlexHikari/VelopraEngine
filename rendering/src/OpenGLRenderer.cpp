#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "pch.h"
#include "OpenGLRenderer.h"
#include "stb_image.h"
#include "VE_KeyboardEvent.h"
#include "VE_MouseEvent.h"

OpenGLRenderer* globalRendererInstance = nullptr;

void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height) {
	if (globalRendererInstance) {
		globalRendererInstance->UpdateProjectionMatrix(width, height);
	}
}

OpenGLRenderer::OpenGLRenderer() : window(nullptr), shader(nullptr), model(nullptr), camera(nullptr), aspectRatio(0.0f), projectionMatrix(glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f)){
	globalRendererInstance = this;
}

OpenGLRenderer::~OpenGLRenderer() {
	for (auto& pair : textureCache) {
		glDeleteTextures(1, &pair.second);
	}

	delete shader;
	delete model;
	delete camera;
	
	globalRendererInstance = nullptr;

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
		//VELOPRA_CORE_ERROR("Failed to create GLFW window");
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
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
	model = new Model("model.obj", *this);
	model->GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, -1.0f));

	aspectRatio = 800.0f / 600.0f;

	RegisterInputCallbacks();
	UpdateProjectionMatrix(800,600);
	VELOPRA_CORE_INFO("OpenGL Renderer initialized successfully.");

}

void OpenGLRenderer::RegisterInputCallbacks() {
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetWindowSizeCallback(window, GLFWWindowSizeCallback);
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

void OpenGLRenderer::EndFrame() {
	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Poll for and process events
	glfwPollEvents();
}

GLuint OpenGLRenderer::LoadTexture(const std::string& filePath) {
	//VELOPRA_CORE_INFO("Loading texture: {}", filePath);
	auto it = textureCache.find(filePath);
	if (it != textureCache.end()) {
		//VELOPRA_CORE_TRACE("Texture loaded from cache");
		return it->second;
	}

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		//VELOPRA_CORE_ERROR("Failed to load texture: {}", filePath);
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
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	textureCache[filePath] = textureID;
	//VELOPRA_CORE_INFO("Texture loaded successfully: {}", filePath);
	return textureID;
}

bool OpenGLRenderer::WindowShouldClose() const {
	if (window) {
		return glfwWindowShouldClose(window);
	}
	return true;
}

void OpenGLRenderer::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::shared_ptr<Event> event;

	if (action == GLFW_PRESS) {
		event = std::make_shared<KeyPressedEvent>(key, 0);
	}
	else if (action == GLFW_RELEASE) {
		event = std::make_shared<KeyReleasedEvent>(key);
	}
	else if (action == GLFW_REPEAT) {
		event = std::make_shared<KeyPressedEvent>(key, 1);
	}

	if (event) {
		VELOPRA_CORE_TRACE("Posting event: {}", event->ToString());
		Core::Instance().GetEventQueue()->PushEvent(event);
	}
}

void OpenGLRenderer::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	auto event = std::make_shared<MouseMovedEvent>(static_cast<float>(xpos), static_cast<float>(ypos));
	VELOPRA_CORE_TRACE("Posting event: {}", event->ToString());
	Core::Instance().GetEventQueue()->PushEvent(event);
}

void OpenGLRenderer::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	std::shared_ptr<Event> event;

	if (action == GLFW_PRESS) {
		event = std::make_shared<MouseButtonPressedEvent>(button);
	}
	else if (action == GLFW_RELEASE) {
		event = std::make_shared<MouseButtonReleasedEvent>(button);
	}

	if (event) {
		VELOPRA_CORE_TRACE("Posting event: {}", event->ToString());
		Core::Instance().GetEventQueue()->PushEvent(event);
	}
}

void OpenGLRenderer::UpdateProjectionMatrix(int width, int height) {

	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
	// Update viewport as well
	glViewport(0, 0, width, height);
}
#endif