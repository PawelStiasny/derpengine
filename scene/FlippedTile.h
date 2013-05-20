#ifndef FLIPPEDTILE_H
#define FLIPPEDTILE_H

#include "../core/Geometry.h"
#include "../core/Material.h"

/// Represents a flat tile
class FlippedTile : public Geometry
{
public:
	FlippedTile();
	~FlippedTile();

private:
	static const GLfloat s_vertex_data[4*3], s_normal_data[4*3], s_uv_data[4*2];
	static const GLushort s_index_data[6];
};

#endif
