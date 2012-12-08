#include "MechBody.h"

MechBody::MechBody()
{
	quad_obj = gluNewQuadric();
	gluQuadricTexture(quad_obj, GL_TRUE);
}

void MechBody::doRender(RenderingContext *rc)
{
	gluSphere(quad_obj, 0.7, 20, 20);
}
