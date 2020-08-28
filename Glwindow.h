#pragma once

#include <stdio.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Glwindow
{
	GLint width, height;
	GLint buffer_width, buffer_height;

	GLFWwindow* mainWindow;

public:
	Glwindow();
	Glwindow(GLint window_width, GLint window_height);
	~Glwindow();

	void Initialize();
};

