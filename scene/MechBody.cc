#include "MechBody.h"

MechBody::MechBody()
{
	allocCount(21 * 21, 20 * 20 * 2);
	constructSphere(0.7f, 20, 20, 4.0f, 2.0f);
	syncBuffers();
}

