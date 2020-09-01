#include "Shader.h"

std::string Shader::ReadFromFile(const char* fileLocation) {
	std::ifstream fileStream(fileLocation, std::ios::in);
	std::string shaderText = "";

	if (!fileStream.is_open()) {
		printf("File not found! Failed to create %s!", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		shaderText.append(line + "\n");
	}

	fileStream.close();
	printf("Successfully read from file\n");
	return shaderText;
}

void Shader::CreateShaders(const char* vertexLocation, const char* fragmentLocation) {
	std::string vertexString, fragmentString;
	vertexString = ReadFromFile(vertexLocation);
	fragmentString = ReadFromFile(fragmentLocation);

	vShader = vertexString.c_str();
	fShader = fragmentString.c_str();

	CompileShaders(vShader, fShader);
}

void Shader::CompileShaders(const char* vertexCode, const char* fragmentCode) {
	GLint ivResult;
	char errorLog[1024];
	
	GLuint vShader, fShader;
	const GLchar* shaderCode[2];
	GLint shaderCodeLength[2];

	// Setting up code chars for glShaderSource
	shaderCode[0] = vertexCode;
	shaderCode[1] = fragmentCode;

	// Setting up code length of shaders for glShaderSource
	shaderCodeLength[0] = (GLint)strlen(vertexCode);
	shaderCodeLength[1] = (GLint)strlen(fragmentCode);

	shaderID = glCreateProgram();

	if (!shaderID) {
		printf("Shader Program could not be created");
		return;
	}

	// Compiling Vertex Shader
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &shaderCode[0], &shaderCodeLength[0]);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &ivResult);
	if (!ivResult) {
		glGetShaderInfoLog(vShader, sizeof(errorLog), NULL, errorLog);
		printf("Vertex Shader failed to compile: %s", errorLog);
		return;
	}


	// Compiling Fragment Shader
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &shaderCode[1], &shaderCodeLength[1]);
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &ivResult);
	if (!ivResult) {
		glGetShaderInfoLog(fShader, sizeof(errorLog), NULL, errorLog);
		printf("Fragment shader failed to compile: %s", errorLog);
		return;
	}

	// Attaching and Linking Shaders to Program
	glAttachShader(shaderID, vShader);
	glAttachShader(shaderID, fShader);
	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &ivResult);
	if (!ivResult) {
		glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
		printf("Shader Program Failed to Link: %s", errorLog);
		return;
	}

	// Validates Program
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &ivResult);
	if (!ivResult) {
		glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
		printf("Shader Program Failed to Validate: %s", errorLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");

	// Destroying shaders that are now linked
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	printf("Successfully compiled and linked\n");
}

void Shader::UseShader() {
	glUseProgram(shaderID);
}