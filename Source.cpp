#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Glwindow.h"

Glwindow* window;

unsigned int indices[] = {
	// Back Side
	0,1,3,
	0,2,3,
	//Front Side
	4,5,7,
	4,6,7,
	// Left Side
	4,5,1,
	4,0,1,
	// Right Side
	6,7,3,
	6,2,3,
	// Top Side
	4,0,2,
	4,6,2,
	// Bottom Side
	1,5,3,
	5,7,3
};

GLfloat vertices[] = {
	// Back four vertices
	-1.0f,1.0f,-1.0f, // Back upper left - 0
	-1.0f,-1.0f,-1.0f, // Back lower left - 1
	1.0f,1.0f,-1.0f, // Back upper right - 2
	1.0f,-1.0f,-1.0f, // Back lower right - 3
	// Front four vertices
	-1.0f,1.0f,1.0f, // Front upper left - 4
	-1.0f,-1.0f,1.0f, // Front lower left - 5
	1.0f,1.0f,1.0f, // Front upper right - 6
	1.0f,-1.0f,1.0f // Front lower right - 7
};

int main() {
	window = new Glwindow();
	window->Initialize();

	while (!window->ShouldWindowClose()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window->SwapFrameBuffers();
		glfwPollEvents();
	}

	return 0;
}