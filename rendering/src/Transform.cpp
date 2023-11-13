#include "Transform.h"

Transform::Transform() : position(0.0f), rotation(0.0f), scale(1.0f) {}

glm::mat4 Transform::GetModelMatrix() const {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);
	return model;
}

void Transform::SetPosition(const glm::vec3& pos) {
	position = pos;
}

void Transform::SetRotation(const glm::vec3& rot) {
	rotation = rot;
}

void Transform::SetScale(const glm::vec3& scale) {
	this->scale = scale;
}
