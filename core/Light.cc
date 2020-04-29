#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include "../common.h"

#include "Light.h"
#include "RenderingContext.h"

DirectionalLight::DirectionalLight()
{
	addMember(&camera);
	shadowmap_rc = NULL;
	shadowmap = NULL;
	fb = NULL;
}

DirectionalLight::~DirectionalLight()
{
	if (shadowmap) {
		delete fb;
		delete shadowmap_rc;
		delete shadowmap;
	}
}

void DirectionalLight::buildShadowMap(GraphNode *scene, GraphNode *reference)
{
	// create the rendering context and framebuffer first time a shadowmap is
	// built
	if (!shadowmap) {
		shadowmap_rc = new RenderingContext;
		shadowmap_rc->reshape(1024, 1024);
		shadowmap = new DepthFramebufferTexture(1024, 1024);
		fb = new Framebuffer(1024, 1024);
		fb->setDepthTexture(shadowmap);
	}

	camera.setTarget(reference);
	// camera position = light position + reference position
	camera.setPosition(reference->getWorldCoordinates().xyz());
	float cam_distance = glm::length(getWorldCoordinates());
	camera.setClippingDistance(cam_distance - 3.0f, cam_distance + 5.0f);
	camera.setFrustrum(15.0f);
	shadowmap_rc->setCamera(&camera);

	{
		Framebuffer::FramebufferSelection fs(*fb);
		shadowmap_rc->clear();
		scene->depthRender(shadowmap_rc);
	}
}

void DirectionalLight::use(GLSLProgram *shaders)
{
	glm::vec4 light_vec = getWorldCoordinates();
	light_vec.w = 0;
	shaders->setUniformLight(light_vec);

	// If a shadowmap has been built, use it
	if (shadowmap) {
		shadowmap->use(shaders->TEXUNIT_SHADOWMAP);

		glm::mat4 viewport_to_tex(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);

		shaders->setUniformShadowVP(
				viewport_to_tex *
				camera.getProjectionMatrix(1.0f) * 
				camera.getViewMatrix());
	}
}

