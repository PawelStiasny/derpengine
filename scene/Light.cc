#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Light.h"
#include "../ShadowmapRenderingContext.h"
#include "MechBody.h"


void DirectionalLight::buildShadowMap(GraphNode *scene, GraphNode *reference)
{
	GLint prev_draw_buffer;
	glGetIntegerv(GL_DRAW_BUFFER, &prev_draw_buffer);

	ShadowmapRenderingContext shadowmap_rc;
	shadowmap.bindFramebuffer();
	glDrawBuffer(GL_NONE);
	// back face shadows
	//glCullFace(GL_FRONT);

	shadowmap_rc.clear();
	camera.setTarget(reference);
	// camera position = light position + reference position
	camera.setPosition(reference->getWorldCoordinates().xyz());
	float cam_distance = glm::length(getWorldCoordinates());
	camera.setClippingDistance(cam_distance - 1.5f, cam_distance + 3.0f);
	camera.setFrustrum(10.0f);
	shadowmap_rc.setCamera(&camera);
	shadowmap_rc.reshape(1024, 1024);

	scene->render(&shadowmap_rc);

	shadowmap.unbindFramebuffer();
	glDrawBuffer(prev_draw_buffer);
	//glCullFace(GL_BACK);
}

void DirectionalLight::use(GLSLProgram *shaders)
{
	glm::vec4 light_vec = getWorldCoordinates();
	light_vec.w = 0;
	shaders->setUniformLight(light_vec);
	shadowmap.use(shaders->shadowmap_tex_sampler);

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

DirectionalLight::DirectionalLight()
{
	addMember(&camera);
	//MechBody *mb = new MechBody;
	//Material *m = new Material;
	//m->ambient = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	//m->diffuse = glm::vec4(1.0f);
	//m->specular = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	//m->shininess = 10.0f;
	//m->texture = new Texture("textures/metal.bmp");
	//mb->setMaterial(m);
	//camera.addMember(mb);
}

DirectionalLight::~DirectionalLight()
{
}
