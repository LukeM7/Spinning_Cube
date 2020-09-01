#include "Glwindow.h"

Glwindow::Glwindow() : width(1920), height(1080) {}
Glwindow::Glwindow(GLint window_width, GLint window_height) : width(window_width), height(window_height) {}

Glwindow::~Glwindow() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void Glwindow::Initialize() {
	glewExperimental = GL_TRUE;

	if (!glfwInit()) {
		printf("GLFW failed to initialize");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "The Cube", NULL, NULL);

	if (!mainWindow) {
		printf("Window failed to create");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(mainWindow);

	if (glewInit() != GLEW_OK) {
		printf("Glew failed to initialize");
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glfwGetFramebufferSize(mainWindow, &buffer_width, &buffer_height);
	glViewport(0, 0, buffer_width, buffer_height);

	return;
}