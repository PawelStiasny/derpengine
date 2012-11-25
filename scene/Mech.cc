#include "Mech.h"

/// Constructs the mech body and its members
Mech::Mech()
{
	body = new MechBody();
	addMember(body);
	leg[0] = new MechLeg();
	leg[0]->setPosition(-1.0f, -1.0f, 0.0f);
	addMember(leg[0]);
	leg[1] = new MechLeg();
	leg[1]->setPosition(-1.0f, 1.0f, 0.0f);
	addMember(leg[1]);
}

void Mech::doRender()
{

}
