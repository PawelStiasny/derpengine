#ifndef RENDERINGCONTEXT_H
#define RENDERINGCONTEXT_H

#include <glm/glm.hpp>

#include "scene/GraphNode.h"

class RenderingContext
{
public:
	RenderingContext(GraphNode *scene);
	RenderingContext();
	GraphNode* getScene();

	void update();
	void setCamera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLfloat obj_x, GLfloat obj_y, GLfloat obj_z);
	void setCamera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GraphNode *object);

	void pushMatrix();
	void popMatrix();

	const glm::mat4& getModelMatrix();
	void setModelMatrix(glm::mat4& m);

	GLuint program_id;

private:
	glm::mat4 mvp, m_model, m_view, m_projection;
	std::list<glm::mat4> matrix_stack;
	GraphNode *scene;

	void updateMatrix();
};

#endif
