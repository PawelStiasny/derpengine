/*
 * This is a sample animation for the demo.
 * Dirty code ahead.
 */

#include "Animation.h"
#include "../core/GraphNode.h"
#include "../core/Camera.h"

class CameraTracking : public Animation
{
private:
	GraphNode* subject;
	Camera* cam;

public:
	CameraTracking(GraphNode* subject, Camera* cam);
	virtual void update(float timestep);

	float y;
	float rotation;
};
