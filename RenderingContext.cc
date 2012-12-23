#include "SDL.h"
#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "RenderingContext.h"

RenderingContext::RenderingContext(GraphNode *scene)
{
	this->scene = scene;
	vertex_shader = GLSLProgramPool::getInstance()->getDefaultShaders();
	vertex_shader->use();
	m_projection = glm::perspective(60.0f, 4.0f/3.0f, 0.5f, 100.0f);
	m_view = glm::mat4(1.0f);
	m_model = glm::mat4(1.0f);
	updateMatrix();
}

RenderingContext::~RenderingContext()
{
	//delete vertex_shader;
}

GraphNode* RenderingContext::getScene()
{
	return scene;
}

void RenderingContext::update()
{
	// No need to clear color buffer if we always draw the skybox - save some
	// fill time
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
	matrix_stack.clear();
	m_model = glm::mat4(1.0f);
	updateMatrix();

	scene->render(this);
}

void RenderingContext::setCamera(const glm::vec3& pos, const glm::vec3& target)
{
	camera_pos = pos;
	m_view = glm::lookAt(pos, target, glm::vec3(0.0f,1.0f,0.0f));
	updateMatrix();
}

void RenderingContext::setCamera(const glm::vec3& pos, GraphNode *object)
{
	glm::vec3 target = object->getWorldCoordinates().xyz();
	setCamera(pos, target);
}

glm::vec3 RenderingContext::getCameraPos()
{
	return camera_pos;
}

void RenderingContext::reshape(int w, int h)
{
	m_projection = glm::perspective(60.0f, (float)w/(float)h, 0.5f, 200.0f);
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

void RenderingContext::setTextureSampler(GLuint i)
{
	vertex_shader->setUniformTexSampler(i);
}

void RenderingContext::setMaterial(Material *m)
{
	m->use();
	vertex_shader = m->getShaders();
	updateMatrix();
}

const glm::mat4 & RenderingContext::getModelMatrix()
{
	return m_model;
}

void RenderingContext::setModelMatrix(glm::mat4 &m)
{
	m_model = m;
	updateMatrix();
}

void RenderingContext::updateMatrix()
{
	vertex_shader->setUniformMVP(m_model, m_view, m_projection);
}

