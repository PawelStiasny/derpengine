#include "Mech.h"

/// Constructs the mech body and its members
Mech::Mech()
{
	body = new MechBody();
	addMember(body);

	leg[0] = new MechLeg(0.6, 0.3);
	leg[0]->setPosition(-1.0f, 0.0f, 0.0f);
	leg[0]->setRotation(80.0f, 0.0f, 0.0f);
	addMember(leg[0]);
	leg[1] = new MechLeg(0.6, 0.3);
	leg[1]->setPosition(1.0f, 0.0f, 0.0f);
	leg[1]->setRotation(90.0f, 0.0f, 0.0f);
	addMember(leg[1]);

	leg[2] = new MechLeg(2, 0.2);
	leg[2]->setPosition(0.0f, 0.0f, 0.6f);
	leg[2]->setRotation(12.0f, 0.0f, 0.0f);
	leg[0]->addMember(leg[2]);
	leg[3] = new MechLeg(2, 0.2);
	leg[3]->setPosition(0.0f, 0.0f, 0.6f);
	leg[3]->setRotation(12.0f, 0.0f, 0.0f);
	leg[1]->addMember(leg[3]);
}

