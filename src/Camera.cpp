#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


void camera::Camera::processCameraMovement(Direction movement_direction, float deltatime) {
	float velocity{ speed * deltatime };

	if (movement_direction == Direction::Forward) {
		position += velocity * glm::vec3{ direction.x, direction.y, direction.z };
	}
	else if (movement_direction == Direction::Left) {
		position -= velocity * right;
	}
	else if (movement_direction == Direction::Backward) {
		position -= velocity * glm::vec3{ direction.x, direction.y, direction.z };
	}
	else if (movement_direction == Direction::Right) {
		position += velocity * right;
	}
}

void camera::Camera::processCameraRotation(float x_offset, float y_offset) {
	x_offset *= mouse_sensitivity;
	y_offset *= mouse_sensitivity;

	yaw += x_offset;
	pitch += y_offset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	updateCameraVectors();
}

void camera::Camera::processCameraZoom(float offset) {
	constexpr float UP_LIMIT{ 180.0f };
	constexpr float DOWN_LIMIT{ -180.0f };

	zoom -= offset;

	if (zoom > UP_LIMIT) {
		zoom = UP_LIMIT;
	}
	else if (zoom < DOWN_LIMIT) {
		zoom = DOWN_LIMIT;
	}
}

float camera::Camera::getZoom() {
	return zoom;
}

glm::mat4 camera::Camera::getLookAtMatrix() {
	return glm::lookAt(position, position + direction, up);
}

glm::vec3 camera::Camera::getPosition() {
	return position;
}

glm::vec3 camera::Camera::getDirection() {
	return direction;
}

void camera::Camera::updateCameraVectors() {
	glm::vec3 new_direction;
	new_direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	new_direction.y = sin(glm::radians(pitch));
	new_direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	direction = glm::normalize(new_direction);
	right = glm::normalize(glm::cross(direction, world_up));
	up = glm::normalize(glm::cross(right, direction));
}