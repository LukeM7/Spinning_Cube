#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat pitch, GLfloat yaw, GLfloat roll, GLfloat new_move_speed, GLfloat new_turn_speed) :
	camera_position(position), world_up(up), camera_pitch(pitch), camera_yaw(yaw), camera_roll(roll), camera_front(glm::vec3(0.0f,0.0f,-1.0f)), move_speed(new_move_speed), turn_speed(new_turn_speed)
{
	Update();
}

void Camera::Update() {
	camera_front.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
	camera_front.y = sin(glm::radians(camera_pitch));
	camera_front.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
	camera_front = glm::normalize(camera_front);

	camera_right = glm::normalize(glm::cross(camera_front, world_up));
	camera_up = glm::normalize(glm::cross(camera_right, camera_front));
}

void Camera::KeyControl(bool* keys, GLfloat delta_time) {

	GLfloat velocity = move_speed * delta_time;

	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) camera_position += camera_front * velocity;
	
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) camera_position -= camera_right * velocity;

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) camera_position -= camera_front * velocity;

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) camera_position += camera_right * velocity;
}

void Camera::MouseControl(GLfloat x_change, GLfloat y_change) {
	x_change *= turn_speed;
	y_change *= turn_speed;

	camera_yaw += x_change;
	camera_pitch += y_change;

	if (camera_pitch > 89.0f) camera_pitch = 89.0f;
	if (camera_pitch < -89.0f) camera_pitch = -89.0f;

	Update();
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(camera_position, camera_front + camera_position, camera_up);
}