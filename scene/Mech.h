#include "GraphNode.h"
#include "MechBody.h"
#include "MechLeg.h"
#include "Texture.h"

class Mech : public GraphNode
{
private:
	MechBody *body;
	MechLeg *leg[4];
	Texture *tex;

public:
	Mech();
	~Mech();
	void doRender(RenderingContext *rc);
};
