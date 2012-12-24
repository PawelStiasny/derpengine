#include <GL/glew.h>

#include "Tile.h"

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

Tile::Tile(const char *texture_path)
{
	if (texture_path) {
		tex = new Texture(texture_path, false);
		tex->use(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	} else
		tex = NULL;

	vertex_count = 4;
	triangle_count = 2;
	vertex_data = (GLfloat*)s_vertex_data;
	normal_data = (GLfloat*)s_normal_data;
	uv_data = (GLfloat*)s_uv_data;
	index_data = (GLushort*)s_index_data;
}

Tile::~Tile()
{
	if (tex) delete tex;
}

void Tile::doRender(RenderingContext *rc)
{
	if (tex) tex->use(0);
	Geometry::doRender(rc);
}

