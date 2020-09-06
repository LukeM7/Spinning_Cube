#include "Glwindow.h"

Glwindow::Glwindow() : width(1920), height(1080) {
	for (size_t i = 0; i < 1024; i++) keys[i] = 0;
}
Glwindow::Glwindow(GLint window_width, GLint window_height) : width(window_width), height(window_height) {
	for (size_t i = 0; i < 1024; i++) keys[i] = 0;
}

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

	glfwSetKeyCallback(mainWindow, HandleKeys);

	if (glewInit() != GLEW_OK) {
		printf("Glew failed to initialize");
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glfwGetFramebufferSize(mainWindow, &buffer_width, &buffer_height);
	glViewport(0, 0, buffer_width, buffer_height);

	glfwSetWindowUserPointer(mainWindow, this);

	return;
}

void Glwindow::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Glwindow* thisWindow = static_cast<Glwindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if (key >= 0 && key < 1024) {

		if (action == GLFW_PRESS) thisWindow->keys[key] = true;

		else if (action == GLFW_RELEASE) thisWindow->keys[key] = false;
	}
	
}