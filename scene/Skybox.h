#include "../core/GraphNode.h"
#include "FlippedTile.h"
#include "GeometryNode.h"

class Skybox : public GraphNode
{
public:
	Skybox();
	~Skybox();
	virtual void beforeRender(RenderingContext *rc);
	virtual void afterRender(RenderingContext *rc);
	virtual void depthRender(RenderingContext *rc);

private:
	void makeTexturedTile(int index, /*ResourceHandle<Geometry>*/ FlippedTile* t, const char *path);

	GeometryNode *t[6];
	Material m[6];
};

