#include "Mesh.h"

Mesh::Mesh() : VAO(0), VBO(0), IBO(0), index_count(0) {}
Mesh::~Mesh() { ClearMesh(); }

void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int num_vertices, unsigned int num_indices) {
	index_count = num_indices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * num_indices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * num_vertices, vertices, GL_STATIC_DRAW);

	// Defining the data in our VBO for our VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return;
}

void Mesh::RenderMesh() {

}