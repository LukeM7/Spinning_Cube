#pragma once

#include <stdio.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Glwindow
{
	GLint width, height;
	GLint buffer_width, buffer_height;

	GLFWwindow* mainWindow;

	bool keys[1024];

	static void HandleKeys(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	Glwindow();
	Glwindow(GLint window_width, GLint window_height);
	~Glwindow();

	void Initialize();
	bool ShouldWindowClose() { return glfwWindowShouldClose(mainWindow); }
	void SwapFrameBuffers() { return glfwSwapBuffers(mainWindow); }

	GLfloat GetBufferWidth() { return (GLfloat)buffer_width; }
	GLfloat GetBufferHeight() { return (GLfloat)buffer_height; }

	bool* GetKeys() { return keys; }

};

