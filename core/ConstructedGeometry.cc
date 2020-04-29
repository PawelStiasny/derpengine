#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/fast_square_root.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ConstructedGeometry.h"

ConstructedGeometry::ConstructedGeometry()
	: Geometry(false)
{
	construction_mx = glm::mat4(1.0f);
}

// @param vertex_count    hints internal data structures to allocate space for
//                        vertex_count verticies
// @param triangle_count  hints internal data structures to allocate space for
//                        triangle_count triangles
ConstructedGeometry::ConstructedGeometry(
		unsigned int vertex_count,
		unsigned int triangle_count)
	: Geometry(false)
{
	vertices.reserve(vertex_count);
	normals.reserve(vertex_count);
	uvs.reserve(vertex_count);
	indicies.reserve(triangle_count);
	construction_mx = glm::mat4(1.0f);
}

/// Creates a sphere in Geometry's data arrays.
//  Set construction_mx to transform resulting geometry.
void ConstructedGeometry::constructSphere(
		float radius,
		unsigned short slices, unsigned short stacks,
		float u_repeat, float v_repeat)
{
	unsigned short initial_vertex_cursor = vertices.size();
	int i, j;

	for (j = 0; j <= slices; j++) {
		// Rotate around Y-axis by j units
		glm::mat4 rot2 = glm::rotate(
				glm::radians((float)j * (360.0f / (float)slices)),
				glm::vec3(0.0f,1.0f,0.0f));

		for (i = 0; i <= stacks; i++) {
			// Rotate around X-axis by i units
			glm::mat4 rot = glm::rotate(
					rot2,
					glm::radians((float)i * (180.0f / (float)stacks)), 
					glm::vec3(1.0f,0.0f,0.0f));

			glm::vec4 rvec = rot * glm::vec4(0.0f, radius, 0.0f, 1.0f);
			glm::vec3 normal =
				glm::mat3(construction_mx) * glm::fastNormalize(rvec).xyz();
			glm::vec3 pos = (construction_mx * rvec).xyz();

			vertices.insert(vertices.end(), pos);

			normals.insert(normals.end(), normal);

			glm::vec2 uv(
					(float)j / (float)slices * u_repeat,
					(float)i / (float)stacks * v_repeat);
			uvs.insert(uvs.end(), uv);
		}
	}

	for (j = 0; j < slices ; j++) {
		for (i = 0; i < stacks; i++) {
			unsigned short ijvertex = j * (stacks+1) + i + initial_vertex_cursor;
			appendTriangle(
				ijvertex,
				ijvertex + (GLushort)1,
				ijvertex + (stacks+1) + (GLushort)1);

			appendTriangle(
				ijvertex + (stacks+1),
				ijvertex,
				ijvertex + (stacks+1) + 1);
		}
	}

	syncData();
}

/// Creates a cylinder in Geometry's data arrays.
//  Set construction_mx to transform resulting geometry.
void ConstructedGeometry::constructCylinder(
		float radius, float len,
		unsigned short slices, unsigned short stacks, 
		float u_repeat, float v_repeat)
{
	unsigned short initial_vertex_cursor = vertices.size();
	int i, j;

	for (j = 0; j <= slices; j++) {
		glm::mat4 rot = glm::rotate(
				glm::radians(-(float)j * (360.0f / (float)slices)),
				glm::vec3(0.0f,0.0f,1.0f));

		glm::vec3 normal = (construction_mx * rot * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)).xyz();

		for (i = 0; i <= stacks; i++) {
			glm::mat4 trans = glm::translate(
					rot,
					(float)i * (len / (float)stacks) *  
					glm::vec3(0.0f,0.0f,1.0f));

			glm::vec4 rvec = trans * glm::vec4(0.0f, radius, 0.0f, 1.0f);
			glm::vec3 pos = (construction_mx * rvec).xyz();

			vertices.insert(vertices.end(), pos);

			normals.insert(normals.end(), normal);

			glm::vec2 uv(
					(float)j / (float)slices * u_repeat,
					(float)i / (float)stacks * v_repeat);
			uvs.insert(uvs.end(), uv);
		}
	}

	for (j = 0; j < slices; j++) {
		for (i = 0; i < stacks; i++) {
			unsigned short ijvertex = j * (stacks+1) + i + initial_vertex_cursor;
			appendTriangle(
				ijvertex,
				ijvertex + 1,
				ijvertex + (stacks+1) + 1);

			appendTriangle(
				ijvertex + (stacks+1),
				ijvertex,
				ijvertex + (stacks+1) + 1);
		}
	}
	
	syncData();
}

void ConstructedGeometry::constructCap(
		float radius,
		unsigned short slices,
		bool inverted)
{
	unsigned short initial_vertex_cursor = vertices.size();
	int j;

	// Middle vertex
	glm::vec3 mver = (construction_mx * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz();
	vertices.insert(vertices.end(), mver);
	glm::vec3 mnor = (construction_mx * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)).xyz();
	if (inverted) mnor = -mnor;
	normals.insert(normals.end(), mnor);
	uvs.insert(uvs.end(), glm::vec2(0.5f, 0.5f));

	for (j = 0; j <= slices; j++) {
		glm::mat4 rot = glm::rotate(
				glm::radians(-(float)j * (360.0f / (float)slices)),
				glm::vec3(0.0f,0.0f,1.0f));

		glm::vec4 rvec = rot * glm::vec4(0.0f, radius, 0.0f, 1.0f);
		glm::vec3 pos = (construction_mx * rvec).xyz();

		vertices.insert(vertices.end(), pos);

		glm::vec3 normal = (construction_mx * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)).xyz();
		if (inverted) normal = -normal;
		normals.insert(normals.end(), normal);

		glm::vec2 uv = (rot * glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)).xy();
		uv += glm::vec2(0.5f, 0.5f);

		uvs.insert(uvs.end(), uv);
	}

	for (j = 0; j < slices; j++) {
		if (inverted) { 
			appendTriangle(
				j + initial_vertex_cursor + 2,
				j + initial_vertex_cursor + 1,
				initial_vertex_cursor);
		} else {
			appendTriangle(
				j + initial_vertex_cursor + 1,
				j + initial_vertex_cursor + 2,
				initial_vertex_cursor);
		}
	}
	
	syncData();
}

void ConstructedGeometry::appendTriangle(GLushort indicies[3])
{
	for (int i = 0; i > 3; i++)
		this->indicies.push_back(indicies[i]);
}

void ConstructedGeometry::appendTriangle(GLushort i1, GLushort i2, GLushort i3)
{
	indicies.push_back(i1);
	indicies.push_back(i2);
	indicies.push_back(i3);
}

void ConstructedGeometry::syncData()
{
	vertex_count = vertices.size();
	triangle_count = indicies.size() / 3;
	vertex_data = (GLfloat*)vertices.data();
	normal_data = (GLfloat*)normals.data();
	uv_data = (GLfloat*)uvs.data();
	index_data = (GLushort*)indicies.data();

	syncBuffers();
}
