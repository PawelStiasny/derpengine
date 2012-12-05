#include <SDL/SDL.h>

#include "RenderingContext.h"

RenderingContext::RenderingContext(GraphNode *scene)
{
	this->scene = scene;
}


RenderingContext::RenderingContext()
{
	this->scene = new GraphNode;
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

	scene->render(this);
	glFlush();
	SDL_GL_SwapBuffers();
}


void
RenderingContext::setCamera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat obj_x, GLfloat obj_y, GLfloat obj_z)
{
	// TODO: lookat
	updateMatrix();
}


void
RenderingContext::setCamera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GraphNode *object)
{
	// TODO: obtain position
	//setCamera(pos_x, pos_y, pos_z, object->pos.v[0], object->pos.v[1], object->pos.v[2]);
}


void
RenderingContext::pushMatrix()
{
	matrix_stack.push_back(mvp);
}


void
RenderingContext::popMatrix()
{
	mvp = matrix_stack.back();
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
	//glUniformMatrix4fv(glGetUniformLocation(program_id, "t"), 1, GL_FALSE, &mvp[0][0]);
}


