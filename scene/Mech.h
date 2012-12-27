#include "GraphNode.h"
#include "MechBody.h"
#include "MechLeg.h"
#include "MechLauncher.h"
#include "../shaders/Material.h"

class Mech : public GraphNode
{
private:
	MechBody *body;
	MechLauncher *launcher[2];
	MechLeg *leg[4];
	Material *m;

public:
	Mech();
	~Mech();
	void doRender(RenderingContext *rc);
	void bendLeg(int num, float degree);
	float getDistanceToGround();
};
