#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GraphNode.h"

/// Handles rendering of models.
class Geometry : public GraphNode
{
public:
	Geometry();
	~Geometry();
	virtual void doRender(RenderingContext *rc);

protected:
	GLfloat *vertex_data, *normal_data, *uv_data;
	GLushort *index_data;
	GLuint vertex_count, triangle_count;
	enum buffer_object_type { BUF_VERTEX, BUF_NORMAL, BUF_UV };
	GLuint buffer_objects[3];

	void allocCount(GLuint vertex_count, GLuint triangle_count);
	void syncBuffers();
};

#endif
