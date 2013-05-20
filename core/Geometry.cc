#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/fast_square_root.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Geometry.h"

Geometry::Geometry(bool own_memory)
{
	vertex_count = triangle_count = 0;
	vertex_data = normal_data = uv_data = NULL;
	index_data = NULL;
	glGenBuffers(4, buffer_objects);
	glGenVertexArrays(1, &vertex_array_object);

	construction_mx = glm::mat4(1.0f);
	vertex_cursor = index_cursor = 0;
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

/// Creates a sphere in Geometry's data arrays.
//  Arrays of proper size must be allocated beforehand.
//  vertex_cursor and index_cursor have to be set properly and will be advanced
//  accordingly.
//  Set construction_mx to transform resulting geometry.
void Geometry::constructSphere(float radius, int slices, int stacks, float u_repeat, float v_repeat)
{
	unsigned int initial_vertex_cursor = vertex_cursor;
	int i, j;

	if (vertex_count - initial_vertex_cursor < (slices+1) * (stacks+1))
		printf("warning: probably too few vertices allocated to construct a sphere\n");

	for (j = 0; j <= slices; j++) {
		// Rotate around Y-axis by j units
		glm::mat4 rot2 = glm::rotate(
				(float)j * (360.0f / (float)slices),
				glm::vec3(0.0f,1.0f,0.0f));

		for (i = 0; i <= stacks; i++) {
			// Rotate around X-axis by i units
			glm::mat4 rot = glm::rotate(
					rot2,
					(float)i * (180.0f / (float)stacks), 
					glm::vec3(1.0f,0.0f,0.0f));

			glm::vec4 rvec = rot * glm::vec4(0.0f, radius, 0.0f, 1.0f);
			glm::vec3 normal = glm::mat3(construction_mx) * glm::fastNormalize(rvec).xyz();
			glm::vec3 pos = (construction_mx * rvec).xyz();

			memcpy(
					&(vertex_data[vertex_cursor * 3]),
					(float*)glm::value_ptr(pos),
					3*sizeof(float));

			memcpy(
					&(normal_data[vertex_cursor * 3]),
					(float*)glm::value_ptr(normal),
					3*sizeof(float));

			uv_data[vertex_cursor*2] = (float)j / (float)slices * u_repeat;
			uv_data[vertex_cursor*2+1] = (float)i / (float)stacks * v_repeat;

			vertex_cursor++;
		}
	}

	for (j = 0; j < slices ; j++) {
		for (i = 0; i < stacks; i++) {
			int ijvertex = j * (stacks+1) + i + initial_vertex_cursor;
			index_data[index_cursor+0] = ijvertex;
			index_data[index_cursor+1] = ijvertex + 1;
			index_data[index_cursor+2] = ijvertex + (stacks+1) + 1;

			index_data[index_cursor+3] = ijvertex + (stacks+1);
			index_data[index_cursor+4] = ijvertex;
			index_data[index_cursor+5] = ijvertex + (stacks+1) + 1;

			index_cursor += 6;
		}
	}
}

/// Creates a cylinder in Geometry's data arrays.
//  Arrays of proper size must be allocated beforehand.
//  vertex_cursor and index_cursor have to be set properly and will be advanced
//  accordingly.
//  Set construction_mx to transform resulting geometry.
void Geometry::constructCylinder(float radius, float len,
			int slices, int stacks, 
			float u_repeat, float v_repeat)
{
	unsigned int initial_vertex_cursor = vertex_cursor;
	int i, j;

	if (vertex_count - initial_vertex_cursor < (slices+1) * (stacks+1))
		printf("warning: probably too few vertices allocated to construct a cylinder\n");

	for (j = 0; j <= slices; j++) {
		glm::mat4 rot = glm::rotate(
				-(float)j * (360.0f / (float)slices),
				glm::vec3(0.0f,0.0f,1.0f));

		glm::vec3 normal = (construction_mx * rot * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)).xyz();

		for (i = 0; i <= stacks; i++) {
			glm::mat4 trans = glm::translate(
					rot,
					(float)i * (len / (float)stacks) *  
					glm::vec3(0.0f,0.0f,1.0f));

			glm::vec4 rvec = trans * glm::vec4(0.0f, radius, 0.0f, 1.0f);
			glm::vec3 pos = (construction_mx * rvec).xyz();

			memcpy(
					&(vertex_data[vertex_cursor * 3]),
					(float*)glm::value_ptr(pos),
					3*sizeof(float));

			memcpy(
					&(normal_data[vertex_cursor * 3]),
					(float*)glm::value_ptr(normal),
					3*sizeof(float));

			uv_data[vertex_cursor*2] = (float)j / (float)slices * u_repeat;
			uv_data[vertex_cursor*2+1] = (float)i / (float)stacks * v_repeat;

			vertex_cursor++;
		}
	}

	for (j = 0; j < slices; j++) {
		for (i = 0; i < stacks; i++) {
			int ijvertex = j * (stacks+1) + i + initial_vertex_cursor;
			index_data[index_cursor+0] = ijvertex;
			index_data[index_cursor+1] = ijvertex + 1;
			index_data[index_cursor+2] = ijvertex + (stacks+1) + 1;

			index_data[index_cursor+3] = ijvertex + (stacks+1);
			index_data[index_cursor+4] = ijvertex;
			index_data[index_cursor+5] = ijvertex + (stacks+1) + 1;

			index_cursor += 6;
		}
	}
}

void Geometry::constructCap(float radius, int slices, bool inverted)
{
	unsigned int initial_vertex_cursor = vertex_cursor;
	int j;

	if (vertex_count - initial_vertex_cursor < (slices + 2))
		printf("warning: probably too few vertices allocated to construct a cylinder\n");

	// Middle vertex
	glm::vec3 mver = (construction_mx * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz();
	memcpy(
			&(vertex_data[vertex_cursor * 3]),
			(float*)glm::value_ptr(mver),
			3*sizeof(float));
	glm::vec3 mnor = (construction_mx * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)).xyz();
	if (inverted) mnor = -mnor;
	memcpy(
			&(normal_data[vertex_cursor * 3]),
			(float*)glm::value_ptr(mnor),
			3*sizeof(float));
	uv_data[vertex_cursor*2] = 0.5f;
	uv_data[vertex_cursor*2+1] = 0.5f;
	vertex_cursor++;

	for (j = 0; j <= slices; j++) {
		glm::mat4 rot = glm::rotate(
				-(float)j * (360.0f / (float)slices),
				glm::vec3(0.0f,0.0f,1.0f));

		glm::vec4 rvec = rot * glm::vec4(0.0f, radius, 0.0f, 1.0f);
		glm::vec3 pos = (construction_mx * rvec).xyz();

		memcpy(
				&(vertex_data[vertex_cursor * 3]),
				(float*)glm::value_ptr(pos),
				3*sizeof(float));

		glm::vec3 normal = (construction_mx * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)).xyz();
		if (inverted) normal = -normal;
		memcpy(
				&(normal_data[vertex_cursor * 3]),
				(float*)glm::value_ptr(normal),
				3*sizeof(float));

		glm::vec2 uv = (rot * glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)).xy();
		uv += glm::vec2(0.5f, 0.5f);

		memcpy(
				&(uv_data[vertex_cursor * 2]),
				(float*)glm::value_ptr(uv),
				2*sizeof(float));

		vertex_cursor++;
	}

	for (j = 0; j < slices; j++) {
		if (inverted) { 
			index_data[index_cursor+0] = j + initial_vertex_cursor + 2;
			index_data[index_cursor+1] = j + initial_vertex_cursor + 1;
		} else {
			index_data[index_cursor+0] = j + initial_vertex_cursor + 1;
			index_data[index_cursor+1] = j + initial_vertex_cursor + 2;
		}
		index_data[index_cursor+2] = initial_vertex_cursor;

		index_cursor += 3;
	}
}


