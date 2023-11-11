#ifndef VELOPRA_SHADER_H
#define VELOPRA_SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	// Add more uniform functions as needed

private:
	GLuint programID;
	GLuint CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
	std::string ReadFile(const std::string& filepath);
};

#endif // VELOPRA_SHADER_H