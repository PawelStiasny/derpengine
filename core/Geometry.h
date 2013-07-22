#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GraphNode.h"
#include "../util/resource.h"

/// Abstract class handling rendering of meshes.
class Geometry : public SharedResource
{
public:
	virtual ~Geometry();
	void render();

protected:
	// Data used for rendering
	GLfloat *vertex_data, *normal_data, *uv_data;
	GLushort *index_data;
	GLuint vertex_count, triangle_count;

	Geometry(bool own_memory = true);
	void allocCount(GLuint vertex_count, GLuint triangle_count);
	void syncBuffers();

private:
	enum buffer_object_type { BUF_VERTEX, BUF_NORMAL, BUF_UV, BUF_INDICES };
	GLuint buffer_objects[4];
	GLuint vertex_array_object;
	bool own_memory;
};


#endif
