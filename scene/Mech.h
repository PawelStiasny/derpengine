#include "GraphNode.h"
#include "MechBody.h"
#include "MechLeg.h"

class Mech : public GraphNode
{
private:
	MechBody *body;
	MechLeg *leg[2];

public:
	Mech();

private:
	void doRender();
};
