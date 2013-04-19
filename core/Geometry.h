#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GraphNode.h"
#include "../util/resource.h"

/// Abstract class handling rendering of meshes.
class Geometry : public SharedResource
{
public:
	virtual ~Geometry();
	void render(RenderingContext *rc);

protected:
	// Data used for rendering
	GLfloat *vertex_data, *normal_data, *uv_data;
	GLushort *index_data;
	GLuint vertex_count, triangle_count;

	// Data used for geometry construction
	glm::mat4 construction_mx;
	unsigned int vertex_cursor, index_cursor;

	Geometry();
	void allocCount(GLuint vertex_count, GLuint triangle_count);
	void syncBuffers();

	void constructSphere(float radius, 
			int slices, int stacks, 
			float u_repeat, float v_repeat);

	void constructCylinder(float radius, float len,
			int slices, int stacks, 
			float u_repeat, float v_repeat);

	void constructCap(float radius, int slices, bool inverted);

private:
	enum buffer_object_type { BUF_VERTEX, BUF_NORMAL, BUF_UV };
	GLuint buffer_objects[3];
};

#endif
