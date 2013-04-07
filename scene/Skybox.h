#include "GraphNode.h"
#include "Tile.h"
#include "GeometryNode.h"

class Skybox : public GraphNode
{
public:
	Skybox();
	~Skybox();
	virtual void beforeRender(RenderingContext *rc);
	virtual void afterRender(RenderingContext *rc);

private:
	void makeTexturedTile(int index, Tile *t, const char *path);

	GeometryNode *t[6];
	Material m[6];
};

