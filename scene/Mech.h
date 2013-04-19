#ifndef MECH_H
#define MECH_H

#include "../core/GraphNode.h"
#include "MechBody.h"
#include "MechLeg.h"
#include "MechLauncher.h"
#include "GeometryNode.h"
#include "../core/Material.h"

class Mech : public GraphNode
{
private:
	MechBody *body;
	MechLauncher *launcher[2];
	GeometryNode *leg[4];

public:
	Mech();
	~Mech();
	void doRender(RenderingContext *rc);
	void bendLeg(int num, float degree);
	float getDistanceToGround();
};

#endif
