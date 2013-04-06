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
	GeometryNode *t[6];
	Material *m;
};

