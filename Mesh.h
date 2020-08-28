#pragma once

#include <GL/glew.h>

class Mesh
{
	GLuint VAO, VBO, IBO;
	GLsizei index_count;

public:
	Mesh();
	~Mesh();

	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int num_vertices, unsigned int num_indices);
	void RenderMesh();
	void ClearMesh();

};

