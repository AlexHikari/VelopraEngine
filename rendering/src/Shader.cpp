#include "Shader.h"
#include "VE_Logger.h"
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexSrc = ReadFile(vertexPath);
	std::string fragmentSrc = ReadFile(fragmentPath);

	// Compile shaders and link program
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

	// Create program and link shaders
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	// Check for linking errors and clean up shaders
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
		VELOPRA_CORE_ERROR("Shader link failure: {}",infoLog.data());
		glDeleteProgram(programID);
	}
	glDetachShader(programID, vertexShader);
	glDetachShader(programID, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(programID);
}

void Shader::Bind() const {
	glUseProgram(programID);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

GLuint Shader::CompileShader(unsigned int type, const std::string& source) {
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	// Check for compile errors
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
		VELOPRA_CORE_ERROR("Shader compilation failure: {}",infoLog.data());
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

int Shader::GetUniformLocation(const std::string& name) {
	return glGetUniformLocation(programID, name.c_str());
}

void Shader::SetUniform1i(const std::string& name, int value) {
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

std::string Shader::ReadFile(const std::string& filepath) {
	std::ifstream fileStream(filepath, std::ios::in);
	if (!fileStream.is_open()) {
		VELOPRA_CORE_ERROR("Could not open file {}", filepath);
		return "";
	}
	std::stringstream sstr;
	sstr << fileStream.rdbuf();
	return sstr.str();
}