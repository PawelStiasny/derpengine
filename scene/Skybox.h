#include "GraphNode.h"
#include "Tile.h"

class Skybox : public GraphNode
{
public:
	Skybox();
	~Skybox();
	virtual void doRender(RenderingContext *rc);

private:
	Tile *t[6];
};

