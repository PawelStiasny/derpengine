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

	virtual const glm::mat4 getProjectionMatrix(float aspect_ratio = 4.0/3.0) = 0;
	const glm::mat4 getViewMatrix();

protected:
	glm::vec3 target;
	float clip_near, clip_far;
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera();
	void setFrustrum(float fov, float clip_near, float clip_far);

	virtual const glm::mat4 getProjectionMatrix(float aspect_ratio = 4.0/3.0);

private:
	float fov;
};

class OrthogonalCamera : public Camera
{
public:
	virtual const glm::mat4 getProjectionMatrix(float aspect_ratio = 4.0/3.0);
};

#endif
