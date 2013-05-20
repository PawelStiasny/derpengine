#include "../core/GraphNode.h"
#include "GeometryNode.h"
#include "Tile.h"
#include <GL/glu.h>

class MechLauncher : public GraphNode
{
public:
	MechLauncher();

private:
	void doRender(RenderingContext *rc);
};
