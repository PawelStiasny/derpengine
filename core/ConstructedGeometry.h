#ifndef CONSTRUCTEDGEOMETRY_H
#define CONSTRUCTEDGEOMETRY_H

#include "Geometry.h"
#include <vector>

class ConstructedGeometry : public Geometry
{
public:
	glm::mat4 construction_mx;

	ConstructedGeometry();
	ConstructedGeometry(
			unsigned int vertex_count,
			unsigned int triangle_count);

	void constructSphere(float radius, 
			unsigned short slices, unsigned short stacks,
			float u_repeat, float v_repeat);

	void constructCylinder(float radius, float len,
			unsigned short slices, unsigned short stacks,
			float u_repeat, float v_repeat);

	void constructCap(float radius, unsigned short slices, bool inverted);

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLushort> indicies;

	void appendTriangle(GLushort indicies[3]);
	void appendTriangle(GLushort i1, GLushort i2, GLushort i3);
	void syncData();
};

#endif
