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

	void allocCount(GLuint vertex_count, GLuint triangle_count);
};

#endif
