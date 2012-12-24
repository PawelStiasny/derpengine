#include "Geometry.h"

Geometry::Geometry()
{
	vertex_count = triangle_count = 0;
	vertex_data = normal_data = uv_data = NULL;
	index_data = NULL;
}


Geometry::~Geometry()
{
	// Do not free by default - our pointers may point to static or shared data.
	// If you allocate buffers in a subclass, you need to free them yourself.
}


void Geometry::doRender(RenderingContext *rc)
{
	// Drop out early if there is nothing to render
	if (triangle_count == 0)
		return;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex_data);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normal_data);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, uv_data);

	glDrawElements(GL_TRIANGLES, 3 * triangle_count, GL_UNSIGNED_SHORT, index_data);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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


