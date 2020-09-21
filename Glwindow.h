#pragma once

#include <stdio.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Glwindow
{
	GLint width, height;
	GLint buffer_width, buffer_height;

	GLfloat x_change, y_change;
	GLfloat prev_x, prev_y;

	GLFWwindow* mainWindow;

	bool keys[1024];
	bool mouse_has_moved{ true };

	static void HandleKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void HandleMouse(GLFWwindow* window, double xpos, double ypos);

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
	bool HasMouseMoved() { return mouse_has_moved; }

	GLfloat Get_X_Change();
	GLfloat Get_Y_Change();
};

