/*
 * This is a sample animation for the demo.
 * Dirty code ahead.
 */

#include "Animation.h"
#include "../scene/Mech.h"
#include "../scene/Terrain.h"

class MechWalk : public Animation
{
private:
	Mech* subject;
	Terrain* terrain;
	float leg_bend;
	int leg_state;

public:
	int move_forward;

	MechWalk(Mech* subject, Terrain* terrain);
	virtual void update(float timestep);
};
