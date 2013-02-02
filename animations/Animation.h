#ifndef ANIMATION_H
#define ANIMATION_H

/// Abstact class for animations
class Animation
{
public:
	virtual void update(float timestep) = 0;
};

#endif
