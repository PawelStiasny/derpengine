#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Light.h"
#include "ShadowmapRenderingContext.h"

DirectionalLight::DirectionalLight()
{
	addMember(&camera);
	shadowmap_rc = NULL;
	shadowmap = NULL;
}

DirectionalLight::~DirectionalLight()
{
	if (shadowmap) {
		delete shadowmap_rc;
		delete shadowmap;
	}
}

void DirectionalLight::buildShadowMap(GraphNode *scene, GraphNode *reference)
{
	GLint prev_draw_buffer;
	glGetIntegerv(GL_DRAW_BUFFER, &prev_draw_buffer);

	// create the rendering context and framebuffer first time a shadowmap is
	// built
	if (!shadowmap) {
		shadowmap_rc = new ShadowmapRenderingContext;
		shadowmap = new DepthFramebufferTexture;
	}

	shadowmap->bindFramebuffer();
	glDrawBuffer(GL_NONE);
	// back face shadows
	//glCullFace(GL_FRONT);

	camera.setTarget(reference);
	// camera position = light position + reference position
	camera.setPosition(reference->getWorldCoordinates().xyz());
	float cam_distance = glm::length(getWorldCoordinates());
	camera.setClippingDistance(cam_distance - 3.0f, cam_distance + 5.0f);
	camera.setFrustrum(15.0f);
	shadowmap_rc->setCamera(&camera);
	shadowmap_rc->reshape(1024, 1024);

	shadowmap_rc->clear();
	scene->render(shadowmap_rc);

	shadowmap->unbindFramebuffer();
	glDrawBuffer(prev_draw_buffer);
	//glCullFace(GL_BACK);
}

void DirectionalLight::use(GLSLProgram *shaders)
{
	glm::vec4 light_vec = getWorldCoordinates();
	light_vec.w = 0;
	shaders->setUniformLight(light_vec);

	// If a shadowmap has been built, use it
	if (shadowmap) {
		shadowmap->use(shaders->shadowmap_tex_sampler);

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

