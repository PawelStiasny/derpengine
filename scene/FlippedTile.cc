#include "../common.h"

#include "FlippedTile.h"
#include "../core/GLSLProgram.h"

const GLfloat FlippedTile::s_vertex_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
};

const GLfloat FlippedTile::s_normal_data[] = {
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f
};
const GLfloat FlippedTile::s_uv_data[] = {
	0.0f, 1.0f, 
	1.0f, 1.0f, 
	1.0f, 0.0f, 
	0.0f, 0.0f, 
};

const GLushort FlippedTile::s_index_data[] = {
	0, 2, 1,
	0, 3, 2
};

FlippedTile::FlippedTile()
	: Geometry(false)
{
	vertex_count = 4;
	triangle_count = 2;
	vertex_data = (GLfloat*)s_vertex_data;
	normal_data = (GLfloat*)s_normal_data;
	uv_data = (GLfloat*)s_uv_data;
	index_data = (GLushort*)s_index_data;
	syncBuffers();
}

FlippedTile::~FlippedTile()
{
}

