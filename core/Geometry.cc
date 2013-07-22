#include "Geometry.h"

// @param own_memory specifies if destructor should release _data arrays
Geometry::Geometry(bool own_memory)
{
	vertex_count = triangle_count = 0;
	vertex_data = normal_data = uv_data = NULL;
	index_data = NULL;
	glGenBuffers(4, buffer_objects);
	glGenVertexArrays(1, &vertex_array_object);

	this->own_memory = own_memory;
}


Geometry::~Geometry()
{
	if (own_memory) {
		delete[] vertex_data;
		delete[] uv_data;
		delete[] normal_data;
		delete[] index_data;
	}
	glDeleteBuffers(3, buffer_objects);
	glDeleteVertexArrays(1, &vertex_array_object);
}


void Geometry::render()
{
	// Drop out early if there is nothing to render
	if (triangle_count == 0)
		return;

	glBindVertexArray(vertex_array_object);
	glDrawElements(GL_TRIANGLES, 3 * triangle_count, GL_UNSIGNED_SHORT, 0);
}


/// Dynamically allocates all buffers and sets counts
void Geometry::allocCount(GLuint vertex_count, GLuint triangle_count)
{
	this->vertex_count = vertex_count;
	this->triangle_count = triangle_count;

	vertex_data = new GLfloat[vertex_count * 3];
	normal_data = new GLfloat[vertex_count * 3];
	uv_data = new GLfloat[vertex_count * 2];
	index_data = new GLushort[triangle_count * 3];
}

/// Copies data into buffer objects
void Geometry::syncBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, 
			vertex_count * 3 * sizeof(GLfloat), vertex_data,
			GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, 
			vertex_count * 3 * sizeof(GLfloat), normal_data,
			GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_UV]);
	glBufferData(GL_ARRAY_BUFFER, 
			vertex_count * 2 * sizeof(GLfloat), uv_data,
			GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_objects[BUF_INDICES]);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			3 * triangle_count * sizeof(GLushort),
			index_data,
			GL_STATIC_DRAW);

	glBindVertexArray(vertex_array_object);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_NORMAL]);
	glVertexAttribPointer(
			GLSLProgram::ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_UV]);
	glVertexAttribPointer(
			GLSLProgram::ATTR_UV, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_VERTEX]);
	glVertexAttribPointer(
			GLSLProgram::ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_objects[BUF_INDICES]);

	glBindVertexArray(0);
}

