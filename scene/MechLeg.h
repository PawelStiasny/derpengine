#include "GraphNode.h"
#include <GL/glu.h>

class MechLeg : public GraphNode
{
private:
	GLfloat length, radius;
	GLUquadricObj *quad_obj, *quad_obj_inv;

public:
	MechLeg(GLfloat length, GLfloat radius);

private:
	void doRender(RenderingContext *rc);
};
