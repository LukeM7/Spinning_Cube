#include "Glwindow.h"

Glwindow::Glwindow() : width(1920), height(1080), prev_x(0.0f),prev_y(0.0f) {
	for (size_t i = 0; i < 1024; i++) keys[i] = 0;
}
Glwindow::Glwindow(GLint window_width, GLint window_height) : width(window_width), height(window_height), prev_x(0.0f),prev_y(0.0f) {
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
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(mainWindow, HandleKeys);
	glfwSetCursorPosCallback(mainWindow, HandleMouse);

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

GLfloat Glwindow::Get_X_Change() {
	GLfloat newChange = x_change;
	x_change = 0.0f;
	return newChange;
}

GLfloat Glwindow::Get_Y_Change() {
	GLfloat newChange = y_change;
	y_change = 0.0f;
	return newChange;
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

void Glwindow::HandleMouse(GLFWwindow* window, double xpos, double ypos) {
	Glwindow* thisWindow = static_cast<Glwindow*>(glfwGetWindowUserPointer(window));

	if (thisWindow->mouse_has_moved) {
		thisWindow->prev_x = xpos;
		thisWindow->prev_y = ypos;
		thisWindow->mouse_has_moved = false;
	}

	thisWindow->x_change = xpos - thisWindow->prev_x;
	thisWindow->y_change = thisWindow->prev_y - ypos;
	thisWindow->prev_x = xpos;
	thisWindow->prev_y = ypos;
	return;
}