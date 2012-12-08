#include "MechLeg.h"

MechLeg::MechLeg(GLfloat length, GLfloat radius)
{
	this->length = length;
	this->radius = radius;
	quad_obj = gluNewQuadric();
	gluQuadricTexture(quad_obj, GL_TRUE);
}

void MechLeg::doRender(RenderingContext *rc)
{
	gluCylinder(quad_obj, radius, radius, length, 20, 1);
}
