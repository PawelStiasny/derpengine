#include "GraphNode.h"
#include "MechBody.h"
#include "MechLeg.h"
#include "MechLauncher.h"
#include "Texture.h"

class Mech : public GraphNode
{
private:
	MechBody *body;
	MechLauncher *launcher[2];
	MechLeg *leg[4];
	Texture *tex;

public:
	Mech();
	~Mech();
	void doRender(RenderingContext *rc);
};
