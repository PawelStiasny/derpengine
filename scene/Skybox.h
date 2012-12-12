#include "GraphNode.h"
#include "Tile.h"

class Skybox : public GraphNode
{
public:
	Skybox();
	~Skybox();
	virtual void beforeRender(RenderingContext *rc);
	virtual void afterRender(RenderingContext *rc);

private:
	Tile *t[6];
};

