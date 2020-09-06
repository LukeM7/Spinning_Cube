#pragma once

#include <stdio.h>
#include <string>

#include <fstream>

#include <gl/glew.h>

class Shader
{
	const char* vShader;
	const char* fShader;

	GLuint shaderID, uniformModel, uniformProjection, uniformView;

	void CompileShaders(const char* vertexCode, const char* fragmentCode);
	std::string ReadFromFile(const char* fileLocation);
public:
	void CreateShaders(const char* vertexLocation, const char* fragmentLocation);
	void UseShader();
	GLuint GetModel() { return uniformModel; }
	GLuint GetProjection() { return uniformProjection; }
	GLuint GetView() { return uniformView; }
};

