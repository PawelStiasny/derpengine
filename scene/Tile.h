#include "GraphNode.h"
#include "Texture.h"

/// Represents a flat tile with optional texture
class Tile : public GraphNode
{
public:
	Tile(const char *texture_path = NULL);
	~Tile();
	virtual void doRender(RenderingContext *rc);
private:
	static const GLfloat vertex_data[4*3], uv_data[4*2];
	static const GLushort index_data[6];
	Texture *tex;
};

