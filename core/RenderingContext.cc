#include <SDL2/SDL.h>
#include "../common.h"
#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "RenderingContext.h"

#include "../util/ResourceManager.h"

RenderingContext::RenderingContext()
{
	active_camera = &default_cam;
	active_light = NULL;
	env_map_specular = NULL;

	width = 1024;
	height = 768;
	aspect_ratio = 4.0f/3.0f;
	m_projection = glm::perspective(60.0f, 4.0f/3.0f, 0.5f, 100.0f);
	m_view = glm::mat4(1.0f);
	m_model = glm::mat4(1.0f);
}

RenderingContext::~RenderingContext()
{
}

void RenderingContext::clear(bool clear_z)
{
	glViewport(0, 0, (GLint) width, (GLint) height);
	// No need to clear color buffer if we always draw the skybox - save some
	// fill time
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (clear_z) glClear(GL_DEPTH_BUFFER_BIT);

	matrix_stack.clear();
	m_model = glm::mat4(1.0f);
	m_projection = active_camera->getProjectionMatrix(aspect_ratio);
	m_view = active_camera->getViewMatrix();
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
}

const glm::mat4 & RenderingContext::getModelMatrix()
{
	return m_model;
}

void RenderingContext::setModelMatrix(const glm::mat4 &m)
{
	m_model = m;
}

void RenderingContext::setLight(Light *l)
{
	active_light = l;
}

void RenderingContext::setEnvironmentMap(CubeTexture *specular)
{
	env_map_specular = specular;
}

/// Call when a new GLSLProgram is selected
void RenderingContext::sync(GLSLProgram* program)
{
	program->setUniformMVP(
			m_model, m_view, m_projection,
			getCameraPos());
	if (active_light)
		active_light->use(program);
	if (env_map_specular)
		env_map_specular->use(program->TEXUNIT_SPECULAR_CUBEMAP);
}

