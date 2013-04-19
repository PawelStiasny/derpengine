#ifndef TILE_H
#define TILE_H

#include "../core/Geometry.h"
#include "../core/Material.h"

/// Represents a flat tile
//  TODO: move to Geometry::constructTile
class Tile : public Geometry
{
public:
	Tile();
	~Tile();

private:
	static const GLfloat s_vertex_data[4*3], s_normal_data[4*3], s_uv_data[4*2];
	static const GLushort s_index_data[6];
};

#endif
