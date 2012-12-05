#include <SDL/SDL.h>
#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RenderingContext.h"

RenderingContext::RenderingContext(GraphNode *scene)
{
	this->scene = scene;
	m_projection = glm::perspective(60.0f, 4.0f/3.0f, 1.0f, 10.0f);
	m_view = glm::mat4(1.0f);
	m_model = glm::mat4(1.0f);
	updateMatrix();
}


GraphNode *
RenderingContext::getScene()
{
	return scene;
}


void
RenderingContext::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	matrix_stack.clear();
	m_model = glm::mat4(1.0f);
	updateMatrix();

	scene->render(this);
	glFlush();
	SDL_GL_SwapBuffers();
}


void
RenderingContext::setCamera(glm::vec3 pos, glm::vec3 target)
{
	m_view = glm::lookAt(pos, target, glm::vec3(0.0f,1.0f,0.0f));
	updateMatrix();
}


void
RenderingContext::setCamera(glm::vec3 pos, GraphNode *object)
{
	glm::vec3 target = object->getWorldCoordinates(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz();
	setCamera(pos, target);
}


void
RenderingContext::reshape(int w, int h)
{
	m_projection = glm::perspective(60.0f, (float)w/(float)h, 1.0f, 10.0f);
	updateMatrix();
}


void
RenderingContext::pushMatrix()
{
	matrix_stack.push_back(m_model);
}


void
RenderingContext::popMatrix()
{
	m_model = matrix_stack.back();
	matrix_stack.pop_back();
	updateMatrix();
}


const glm::mat4 &
RenderingContext::getModelMatrix()
{
	return m_model;
}


void
RenderingContext::setModelMatrix(glm::mat4 &m)
{
	m_model = m;
	updateMatrix();
}


void
RenderingContext::updateMatrix()
{
	mvp = m_projection * m_view * m_model;
	// TODO: Pass the shader
	glUniformMatrix4fv(glGetUniformLocation(program_id, "t"), 1, GL_FALSE, glm::value_ptr(mvp));
}


