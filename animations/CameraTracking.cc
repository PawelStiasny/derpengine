
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "CameraTracking.h"

CameraTracking::CameraTracking(GraphNode* subject, Camera* cam)
	: subject(subject), cam(cam)
{
	rotation = 0;
	y = 0;
}

void CameraTracking::update(float timestep)
{
	glm::vec3 cam_pos = 
		(glm::rotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f)) * 
		 glm::vec4(0.0f, y, 3.0f, 1.0f)).xyz();
	cam->setPosition(cam_pos);
	cam->setTarget(subject);
	while (rotation > 360.0f) rotation -= 360.0f;
}

