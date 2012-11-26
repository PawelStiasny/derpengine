#include "MechBody.h"

MechBody::MechBody()
{
	quad_obj = gluNewQuadric();
}

void MechBody::doRender()
{
	gluSphere(quad_obj, 0.7, 20, 20);
}
