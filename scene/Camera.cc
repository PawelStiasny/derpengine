#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Camera.h"

Camera::Camera()
{
	fov = 60.0f;
	clip_near = 0.5f;
	clip_far = 200.0f;
	target = glm::vec3(0.0f, 0.0f, 1.0f);
}

void Camera::setTarget(const glm::vec3& coords)
{
	this->target = coords;
}

void Camera::setTarget(GraphNode* reference)
{
	glm::vec3 target = reference->getWorldCoordinates().xyz();
	setTarget(target);
}

void Camera::setFrustrum(float fov, float clip_near, float clip_far)
{
	this->fov = fov;
	this->clip_near = clip_near;
	this->clip_far = clip_far;
}

const glm::mat4 Camera::getProjectionMatrix(float aspect_ratio)
{
	return glm::perspective(fov, aspect_ratio, clip_near, clip_far);
}

const glm::mat4 Camera::getViewMatrix()
{
	glm::vec3 pos = getWorldCoordinates().xyz();
	return glm::lookAt(pos, target, glm::vec3(0.0f,1.0f,0.0f));
}

