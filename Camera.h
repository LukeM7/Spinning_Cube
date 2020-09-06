#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
	glm::vec3 camera_position, camera_front, camera_right, camera_up;
	
	glm::vec3 world_up;

	GLfloat camera_pitch, camera_yaw, camera_roll;
	GLfloat move_speed, turn_speed;

public:
	Camera(glm::vec3 position, glm::vec3 up, GLfloat pitch, GLfloat yaw, GLfloat roll, GLfloat move_speed);
	~Camera();

	void Update();

	void KeyControl(bool* key, GLfloat delta_time);
	glm::mat4 GetViewMatrix();
};

