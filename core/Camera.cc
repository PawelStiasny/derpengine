#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Camera.h"

Camera::Camera()
{
	clip_near = 0.5f;
	clip_far = 150.0f;
	target = glm::vec3(0.0f, 0.0f, 1.0f);
}

PerspectiveCamera::PerspectiveCamera()
{
	fov = 60.0f;
}

OrthogonalCamera::OrthogonalCamera()
{
	half_frustrum_height = 10.0f;
}

void Camera::setTarget(const glm::vec3& coords)
{
	this->target = coords;
}

void Camera::setTarget(GraphNode* reference)
{
	glm::vec4 target = reference->getWorldCoordinates();
	target /= target.w;
	setTarget(target.xyz());
}

void PerspectiveCamera::setFrustrum(float fov, float clip_near, float clip_far)
{
	this->fov = fov;
	this->clip_near = clip_near;
	this->clip_far = clip_far;
}

void OrthogonalCamera::setFrustrum(float height)
{
	half_frustrum_height = height / 2;
}

const glm::mat4 PerspectiveCamera::getProjectionMatrix(float aspect_ratio)
{
	return glm::perspective(fov, aspect_ratio, clip_near, clip_far);
}

const glm::mat4 OrthogonalCamera::getProjectionMatrix(float aspect_ratio)
{
	return glm::ortho(
			-half_frustrum_height * aspect_ratio, half_frustrum_height * aspect_ratio,
			-half_frustrum_height , half_frustrum_height,
			clip_near, clip_far);
}

const glm::mat4 Camera::getViewMatrix()
{
	glm::vec4 wc = getWorldCoordinates();
	glm::vec3 pos = wc.xyz();
	pos /= wc.w;
	return glm::lookAt(pos, target, glm::vec3(0.0f,1.0f,0.0f));
}

