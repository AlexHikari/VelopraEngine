// Transform.h
#ifndef VE_TRANSFORM_H
#define VE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
	Transform();
	glm::mat4 GetModelMatrix() const;

	void SetPosition(const glm::vec3& pos);
	void SetRotation(const glm::vec3& rot); // Euler angles in degrees
	void SetScale(const glm::vec3& scale);

private:
	glm::vec3 position;
	glm::vec3 rotation; // Euler angles
	glm::vec3 scale;
};

#endif // VE_TRANSFORM_H