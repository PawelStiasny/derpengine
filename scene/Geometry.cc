#include "Geometry.h"

Geometry::Geometry()
{
	vertex_count = triangle_count = 0;
	vertex_data = normal_data = uv_data = NULL;
	index_data = NULL;
	glGenBuffers(3, buffer_objects);
}


Geometry::~Geometry()
{
	// Do not free by default - our pointers may point to static or shared data.
	// If you allocate buffers in a subclass, you need to free them yourself.
	
	glDeleteBuffers(3, buffer_objects);
}


void Geometry::doRender(RenderingContext *rc)
{
	// Drop out early if there is nothing to render
	if (triangle_count == 0)
		return;

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_NORMAL]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_UV]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[BUF_VERTEX]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawElements(GL_TRIANGLES, 3 * triangle_count, GL_UNSIGNED_SHORT, index_data);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
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

}

