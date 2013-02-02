/*
 * This is a sample animation for the demo.
 * Dirty code ahead.
 */

#include "Animation.h"

class MechWalk : public Animation
{
private:
	Mech* subject;
	Terrain* terrain;
	float leg_bend;
	int leg_state;

public:
	int move_forward;

	MechWalk(Mech* subject, Terrain* terrain) : subject(subject), terrain(terrain)
	{
		leg_state = 0;
		leg_bend = 30.0f;
		move_forward = 0;
	};

	virtual void update(float timestep)
	{
		subject->bendLeg(0, 35.0f + leg_bend);
		subject->bendLeg(1, 95.0f - leg_bend);
		subject->bendLeg(2, 35.0f + leg_bend);
		subject->bendLeg(3, 95.0f - leg_bend);

		if (move_forward) {
			if (leg_state) {
				leg_bend--;
				if (leg_bend <= 0.0f) leg_state = 0;
			} else {
				leg_bend++;
				if (leg_bend >= 60.0f) leg_state = 1;
			}
		} else {
			leg_state = 0;
			leg_bend = 30.0f;
		}

		glm::vec4 current_pos = subject->getWorldCoordinates();
		current_pos.z += move_forward * timestep;
		glm::vec3 new_pos(current_pos.x, terrain->getHeight(current_pos.x, current_pos.z) + subject->getDistanceToGround(), current_pos.z);
		subject->setPosition(new_pos.x, new_pos.y, new_pos.z);

	}
};
