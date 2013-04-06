#include <GL/glew.h>

#include "Tile.h"
#include "../shaders/GLSLProgram.h"

const GLfloat Tile::s_vertex_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f
};

const GLfloat Tile::s_normal_data[] = {
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f
};
const GLfloat Tile::s_uv_data[] = {
	0.0f, 1.0f, 
	1.0f, 1.0f, 
	1.0f, 0.0f, 
	0.0f, 0.0f, 
};

const GLushort Tile::s_index_data[] = {
	0, 2, 1,
	0, 3, 2
};

Tile::Tile()
{
	vertex_count = 4;
	triangle_count = 2;
	vertex_data = (GLfloat*)s_vertex_data;
	normal_data = (GLfloat*)s_normal_data;
	uv_data = (GLfloat*)s_uv_data;
	index_data = (GLushort*)s_index_data;
	syncBuffers();
}

Tile::~Tile()
{
}

