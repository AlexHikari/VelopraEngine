#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "stb_image.h"
#include "OpenGLRenderer.h"
#include "pch.h"

OpenGLRenderer* globalRendererInstance = nullptr;

void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height) {
	if (globalRendererInstance) {
		globalRendererInstance->UpdateProjectionMatrix(width, height);
	}
}

OpenGLRenderer::OpenGLRenderer() : window(nullptr), shader(nullptr), model(nullptr), camera(nullptr) {
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
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
	model = new Model("model.obj", *this);
	model->GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, -1.0f));

	glfwSetWindowSizeCallback(window, GLFWWindowSizeCallback);

	aspectRatio = 800.0f / 600.0f;
	UpdateProjectionMatrix(800,600);
	VELOPRA_CORE_INFO("OpenGL Renderer initialized successfully.");

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
	//RenderTestTriangle();
	//RenderTestCube();
	// Unbind shader
	shader->Unbind();
}

void OpenGLRenderer::RenderTestTriangle() {
	// Temporary vertices for a triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind Vertex Array Object
	glBindVertexArray(VAO);

	// Copy vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Draw the triangle
	VELOPRA_CORE_INFO("Drawing test triangle.");
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void OpenGLRenderer::RenderTestCube() {
	// Temporary vertices for a cube
	float vertices[] = {
		// Front face
		-0.5f, -0.5f,  0.5f,  // Bottom-left
		 0.5f, -0.5f,  0.5f,  // Bottom-right
		 0.5f,  0.5f,  0.5f,  // Top-right
		-0.5f,  0.5f,  0.5f,  // Top-left

		// Back face
		-0.5f, -0.5f, -0.5f,  // Bottom-left
		 0.5f, -0.5f, -0.5f,  // Bottom-right
		 0.5f,  0.5f, -0.5f,  // Top-right
		-0.5f,  0.5f, -0.5f,  // Top-left
	};

	unsigned int indices[] = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Back face
		4, 5, 6, 6, 7, 4,
		// Left face
		4, 0, 3, 3, 7, 4,
		// Right face
		1, 5, 6, 6, 2, 1,
		// Top face
		3, 2, 6, 6, 7, 3,
		// Bottom face
		4, 5, 1, 1, 0, 4
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	VELOPRA_CORE_INFO("Drawing test cube.");
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void OpenGLRenderer::LogMatrix(const std::string& name, const glm::mat4& mat) {
	VELOPRA_CORE_INFO("{}: [ {:.2f}, {:.2f}, {:.2f}, {:.2f} ]", name, mat[0][0], mat[1][0], mat[2][0], mat[3][0]);
	VELOPRA_CORE_INFO("    [ {:.2f}, {:.2f}, {:.2f}, {:.2f} ]", mat[0][1], mat[1][1], mat[2][1], mat[3][1]);
	VELOPRA_CORE_INFO("    [ {:.2f}, {:.2f}, {:.2f}, {:.2f} ]", mat[0][2], mat[1][2], mat[2][2], mat[3][2]);
	VELOPRA_CORE_INFO("    [ {:.2f}, {:.2f}, {:.2f}, {:.2f} ]", mat[0][3], mat[1][3], mat[2][3], mat[3][3]);
}

void OpenGLRenderer::EndFrame() {
	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Poll for and process events
	glfwPollEvents();
}

GLuint OpenGLRenderer::LoadTexture(const std::string& filePath) {
	VELOPRA_CORE_INFO("Loading texture: {}", filePath);
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
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	textureCache[filePath] = textureID;
	VELOPRA_CORE_INFO("Texture loaded successfully: {}", filePath);
	return textureID;
}

bool OpenGLRenderer::WindowShouldClose() const {
	if (window) {
		return glfwWindowShouldClose(window);
	}
	return true;
}

void OpenGLRenderer::UpdateProjectionMatrix(int width, int height) {

	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
	// Update viewport as well
	glViewport(0, 0, width, height);
}