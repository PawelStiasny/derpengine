#include "MechBody.h"

MechBody::MechBody()
	: ConstructedGeometry(21 * 21, 20 * 20 * 2)
{
	constructSphere(0.7f, 20, 20, 8.0f, 4.0f);
}

