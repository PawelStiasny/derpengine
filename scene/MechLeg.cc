#include "MechLeg.h"

MechLeg::MechLeg(GLfloat length, GLfloat radius)
{
	this->length = length;
	this->radius = radius;
	quad_obj = gluNewQuadric();
}

void MechLeg::doRender()
{
	gluCylinder(quad_obj, radius, radius, length, 20, 1);
}
