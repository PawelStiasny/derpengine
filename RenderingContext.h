#ifndef RENDERINGCONTEXT_H
#define RENDERINGCONTEXT_H

#include <glm/glm.hpp>

#include "scene/GraphNode.h"
#include "shaders/GLSLProgram.h"
#include "scene/Camera.h"

class RenderingContext
{
public:
	RenderingContext(GraphNode *scene);
	~RenderingContext();
	GraphNode* getScene();

	void update();
	void setCamera(Camera *c);
	glm::vec3 getCameraPos();
	void reshape(int w, int h);

	void pushMatrix();
	void popMatrix();
	const glm::mat4& getModelMatrix();
	void setModelMatrix(glm::mat4 &m);

	void setMaterial(Material *m);

private:
	glm::mat4 mvp, m_model, m_view, m_projection;
	std::list<glm::mat4> matrix_stack;
	GraphNode *scene;
	GLSLProgram *active_glsl_program;
	float aspect_ratio;
	Camera default_cam, *active_camera;

	void updateMatrix();
};

#endif
