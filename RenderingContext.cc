#include <SDL2/SDL.h>
#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "RenderingContext.h"

RenderingContext::RenderingContext(GraphNode *scene)
{
	this->scene = scene;
	active_camera = &default_cam;

	active_glsl_program = GLSLProgramPool::getInstance()->getDefaultShaders();
	active_glsl_program->use();

	aspect_ratio = 4.0f/3.0f;
	m_projection = glm::perspective(60.0f, 4.0f/3.0f, 0.5f, 100.0f);
	m_view = glm::mat4(1.0f);
	m_model = glm::mat4(1.0f);

	light_pos = glm::vec4(300.0f, 100.0f, -300.0, 0.0);

	onProgramChange(active_glsl_program);
}

RenderingContext::~RenderingContext()
{
}

GraphNode* RenderingContext::getScene()
{
	return scene;
}

void RenderingContext::update()
{
	// No need to clear color buffer if we always draw the skybox - save some
	// fill time
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	matrix_stack.clear();
	m_model = glm::mat4(1.0f);
	m_projection = active_camera->getProjectionMatrix(aspect_ratio);
	m_view = active_camera->getViewMatrix();
	updateMatrix();

	scene->render(this);
}

void RenderingContext::setCamera(Camera *c)
{
	active_camera = c;
	m_projection = c->getProjectionMatrix(aspect_ratio);
	m_view = c->getViewMatrix();
	updateMatrix();
}

glm::vec3 RenderingContext::getCameraPos()
{
	return active_camera->getWorldCoordinates().xyz();
}

void RenderingContext::reshape(int w, int h)
{
	aspect_ratio = (float)w/(float)h;
	m_projection = active_camera->getProjectionMatrix(aspect_ratio);
	updateMatrix();
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
	onProgramChange(active_glsl_program);
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

void RenderingContext::setLight(const glm::vec4 &new_pos)
{
	light_pos = new_pos;
	active_glsl_program->setUniformLight(new_pos);
}

/// Called when a new GLSL shader program is set as active
void RenderingContext::onProgramChange(GLSLProgram* new_program)
{
	updateMatrix();
	new_program->setUniformLight(light_pos);
}

void RenderingContext::updateMatrix()
{
	active_glsl_program->setUniformMVP(
			m_model, m_view, m_projection,
			getCameraPos());
}

