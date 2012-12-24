#include "MechBody.h"

MechBody::MechBody()
{
	allocCount(22 * 22, 21 * 21 * 2);
	constructSphere(0.7f, 20, 20, 4.0f, 2.0f);
	syncBuffers();
}

