#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "GraphNode.h"

class Camera : public GraphNode
{
public:
	Camera();
	void setTarget(const glm::vec3& coords);
	void setTarget(GraphNode* reference);
	void setFrustrum(float fov, float clip_near, float clip_far);

	const glm::mat4 getProjectionMatrix(float aspect_ratio = 4.0/3.0);
	const glm::mat4 getViewMatrix();

private:
	glm::vec3 target;
	float fov, clip_near, clip_far;
};

#endif
