#include "GraphNode.h"
#include <GL/glu.h>

class MechBody : public GraphNode
{
private:
	GLUquadricObj* quad_obj;

public:
	MechBody();

private:
	void doRender();
};
