#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Glwindow.h"
#include "Mesh.h"
#include "Shader.h"

Glwindow* window;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

const char* vertexShader = "Shaders/shader.vert";
const char* fragmentShader = "Shaders/shader.frag";

float offset = 0.0f;

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


void CreateObject() {
	Mesh* obj = new Mesh();
	obj->CreateMesh(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
	meshList.push_back(obj);

}

void CreateShaderProgram() {
	Shader* shader = new Shader();
	shader->CreateShaders(vertexShader, fragmentShader);
	shaderList.push_back(shader);
}

static float SpinAngle() {
	offset += 1.2f;
	if (offset >= 360.0f) {
		offset -= 360.0f;
	}
	return offset;
}

int main() {
	window = new Glwindow();
	window->Initialize();

	CreateObject();
	CreateShaderProgram();

	GLuint uniformModel = 0, uniformProjection = 0;

	glm::mat4 projection = glm::perspective(45.0f, window->GetBufferWidth() / window->GetBufferHeight(), 0.1f, 100.0f);


	while (!window->ShouldWindowClose()) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();

		uniformModel = shaderList[0]->GetModel();
		uniformProjection = shaderList[0]->GetProjection();

		glm::mat4 model(1.0);
		
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(SpinAngle()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		glUseProgram(0);

		window->SwapFrameBuffers();
		glfwPollEvents();
	}

	return 0;
}

