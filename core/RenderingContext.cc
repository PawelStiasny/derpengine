#include <SDL2/SDL.h>
#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "RenderingContext.h"

#include "../util/ResourceManager.h"

RenderingContext::RenderingContext()
{
	active_camera = &default_cam;
	active_light = NULL;

	active_glsl_program = ResourceManager::getInstance()->getDefaultShaders();

	width = 1024;
	height = 768;
	aspect_ratio = 4.0f/3.0f;
	m_projection = glm::perspective(60.0f, 4.0f/3.0f, 0.5f, 100.0f);
	m_view = glm::mat4(1.0f);
	m_model = glm::mat4(1.0f);

	//light_pos = glm::vec4(300.0f, 100.0f, -300.0, 0.0);

	//onProgramChange(active_glsl_program);
}

RenderingContext::~RenderingContext()
{
}

void RenderingContext::clear()
{
	glViewport(0, 0, (GLint) width, (GLint) height);
	// No need to clear color buffer if we always draw the skybox - save some
	// fill time
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	active_glsl_program->use();
	matrix_stack.clear();
	m_model = glm::mat4(1.0f);
	m_projection = active_camera->getProjectionMatrix(aspect_ratio);
	m_view = active_camera->getViewMatrix();
	onProgramChange(active_glsl_program.getRawPointer());
	//updateMatrix();
	//if (active_light) active_light->use(active_glsl_program);
}

void RenderingContext::setCamera(Camera *c)
{
	active_camera = c;
}

glm::vec3 RenderingContext::getCameraPos()
{
	return active_camera->getWorldCoordinates().xyz();
}

void RenderingContext::reshape(int w, int h)
{
	aspect_ratio = (float)w/(float)h;
	width = w;
	height = h;
}

void RenderingContext::pushMatrix()
{
	matrix_stack.push_back(m_model);
}

void RenderingContext::popMatrix()
{
	m_model = matrix_stack.back();
	matrix_stack.pop_back();
	updateMatrix();
}

void RenderingContext::setMaterial(Material *m)
{
	m->use();
	active_glsl_program = m->getShaders();
	onProgramChange(active_glsl_program.getRawPointer());
}

const glm::mat4 & RenderingContext::getModelMatrix()
{
	return m_model;
}

void RenderingContext::setModelMatrix(const glm::mat4 &m)
{
	m_model = m;
	updateMatrix();
}

void RenderingContext::setLight(Light *l)
{
	active_light = l;
}

void RenderingContext::setEnvironmentMap(CubeTexture *specular)
{
	env_map_specular = specular;
	specular->use(GLSLProgram::specular_cubemap_sampler);
}

/// Called when a new GLSL shader program is set as active
void RenderingContext::onProgramChange(GLSLProgram* new_program)
{
	updateMatrix();
	if (active_light) active_light->use(new_program);
}

void RenderingContext::updateMatrix()
{
	active_glsl_program->setUniformMVP(
			m_model, m_view, m_projection,
			getCameraPos());
}

