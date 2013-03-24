#include "Geometry.h"
#include "../shaders/Material.h"

/// Represents a flat tile with optional texture
class Tile : public Geometry
{
public:
	Tile(const char *texture_path = NULL);
	Tile(Texture *t);
	~Tile();
	virtual void doRender(RenderingContext *rc);

private:
	static const GLfloat s_vertex_data[4*3], s_normal_data[4*3], s_uv_data[4*2];
	static const GLushort s_index_data[6];
	Texture *tex;
};

